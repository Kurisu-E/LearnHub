import os
import subprocess
import sys

def is_link_file(file_path):
  """检查文件是否是链接文件（只有一行且以.html结尾）"""
  try:
    with open(file_path, 'r', encoding='utf-8') as f:
      content = f.read().strip()
      return content.endswith('.html') and len(content.split('\n')) == 1
  except:
    return False

def create_link(link_file, target_file):
  """创建符号链接"""
  try:
    # 先删除原文件
    os.remove(link_file)
    # 创建符号链接
    subprocess.run(['mklink', link_file, target_file], check=True, shell=True)
    print(f"成功创建链接: {link_file} -> {target_file}")
  except subprocess.CalledProcessError as e:
    print(f"创建链接失败: {link_file} -> {target_file}")
    print("请确保以管理员权限运行此脚本")
  except Exception as e:
    print(f"处理文件时出错 {link_file}: {str(e)}")

def process_file(file_path):
  """处理单个文件"""
  if is_link_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
      target_file = f.read().strip()
    create_link(file_path, target_file)

def process_directory(dir_path):
  """处理目录中的所有文件"""
  for root, dirs, files in os.walk(dir_path):
    for file in files:
      if file.endswith('.html'):
        file_path = os.path.join(root, file)
        process_file(file_path)

def main():
  if len(sys.argv) != 2:
    print("用法: python link.py <文件或目录路径>")
    return

  path = sys.argv[1]
  if os.path.isfile(path):
    process_file(path)
  elif os.path.isdir(path):
    process_directory(path)
  else:
    print("路径不存在")

if __name__ == "__main__":
  main()
