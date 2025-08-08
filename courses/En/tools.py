import re
from datetime import datetime, timedelta
from pathlib import Path

def read_markdown_dates(file_path):
  """读取markdown文件中的日期标题"""
  dates = []
  
  try:
    with open(file_path, 'r', encoding='utf-8') as file:
      content = file.read()
      
    # 使用正则表达式匹配 #### 开头的日期标题
    # 格式: #### MM/DD/YYYY {任意内容}
    pattern = r'####\s+(\d{2}/\d{2}/\d{4})\s*\{.*?\}'
    matches = re.findall(pattern, content)
    
    # 将字符串日期转换为datetime对象
    for date_str in matches:
      try:
        date_obj = datetime.strptime(date_str, '%m/%d/%Y')
        dates.append(date_obj)
      except ValueError:
        print(f"警告: 无法解析日期 {date_str}")
        
  except FileNotFoundError:
    print(f"错误: 找不到文件 {file_path}")
    return []
  except Exception as e:
    print(f"错误: 读取文件时出现问题 - {e}")
    return []
  
  # 按日期排序
  dates.sort()
  return dates

def select_dates_by_rule(dates, current_date=None):
  """根据 2^i-1 规则选择日期"""
  if current_date is None:
    current_date = datetime.now()
  
  # 筛选出当前日期之前的日期
  past_dates = [date for date in dates if date < current_date]
  
  if not past_dates:
    return []
  
  selected_dates = []
  i = 1
  
  while True:
    # 计算距离当前日期的天数: 2^i - 1
    days_back = (2 ** i) - 1
    target_date = current_date - timedelta(days=days_back)
    
    # 找到最接近目标日期的实际日期
    closest_date = None
    min_diff = float('inf')
    
    for date in past_dates:
      if date <= target_date:
        diff = abs((target_date - date).days)
        if diff < min_diff:
          min_diff = diff
          closest_date = date
    
    # 如果找到了日期且不在已选列表中，添加到结果
    if closest_date and closest_date not in selected_dates:
      selected_dates.append(closest_date)
    
    # 如果目标日期已经超出了最早的日期，停止循环
    if not past_dates or target_date < min(past_dates):
      break
      
    i += 1
    
    # 防止无限循环
    if i > 20:
      break
  
  # 按日期排序
  selected_dates.sort()
  return selected_dates

def main():
  # 文件路径
  file_path = "En/note.md"
  
  # 读取日期
  dates = read_markdown_dates(file_path)
  
  if not dates:
    print("未找到任何日期标题")
    return
  
  # print("找到的所有日期:")
  # for date in dates:
  #   print(f"  {date.strftime('%m/%d/%Y')}")
  
  # 设置当前日期（可以修改为其他日期进行测试）
  # current_date = datetime(2025, 8, 8)  # 示例中的当前日期
  current_date = datetime.now()  # 使用实际当前日期
  
  print(f"\n当前日期: {current_date.strftime('%m/%d/%Y')}")
  
  # 根据规则选择日期
  selected_dates = select_dates_by_rule(dates, current_date)

  selected_dates.reverse()  # 反转列表，使日期按从近到远排序
  
  print(f"\n选中日期:")
  for i, date in enumerate(selected_dates, 1):
    days_back = (current_date - date).days
    print(f"  {date.strftime('%m/%d/%Y')} (距今 {days_back} 天)(最接近 {2 ** i - 1} 天)")

if __name__ == "__main__":
  main()
