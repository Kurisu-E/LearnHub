from datetime import datetime, timedelta

def calculate_spaced_dates(current_date=None, max_i=9):
  """
  计算当前日期前 2^i-1 天的日期
  
  Args:
    current_date: 当前日期，如果为None则使用今天
    max_i: 最大的i值，默认为10
  
  Returns:
    list: 包含所有计算出的日期的列表
  """
  if current_date is None:
    current_date = datetime.now()
  
  dates = []
  
  for i in range(1, max_i + 1):
    days_back = 2**i - 1
    target_date = current_date - timedelta(days=days_back)
    dates.append(target_date)
  
  return dates

def format_date(date):
  """将日期格式化为 MM/DD/YYYY 格式"""
  return date.strftime('%m/%d/%Y')

def main():
  # 设置当前日期
  # 使用实际当前日期
  current_date = datetime.now()
  
  # 或者设置为示例日期进行测试
  # current_date = datetime(2025, 8, 8)
  
  print(f"当前日期: {format_date(current_date)}")
  print("\n前 2^i-1 天的日期:")
  print("=" * 40)
  
  # 计算并输出日期
  dates = calculate_spaced_dates(current_date, max_i=9)
  
  for i, date in enumerate(dates, 1):
    days_back = 2**i - 1
    formatted_date = format_date(date)
    print(f"i={i:2d}: 2^{i}-1 = {days_back:4d} 天前 → {formatted_date}")

if __name__ == "__main__":
  # 运行主程序
  main()
  
  print("="*40)
