---
title: Visual Studio Code Note
author: 吴玉灿
---

学习链接：

- VSCode 官方文档[^docs]
  [^docs]: [VSCode 官方文档](https://code.visualstudio.com/docs)
  
目录：

[toc]

<!-- ---

### 1&emsp;安装 Setup

应用软件默认安装在 `C:\Users\{Username}\AppData\Local\Programs\Microsoft VS Code`.

可以通过 `code [options] [paths...]` 命令行启动 VSCode

VSCode 是建立在 Electron 和 Chromium 的网络栈功能之上的，因此 VSCode 用户可以获得 Google Chrome 中可用的许多网络支持.

VSCode 提供 [VSCode 在线网站](https://vscode.dev/)，可以直接通过在网站进行编辑. -->

---

### 2&emsp;入门 Start

#### 2.1&emsp;教程 Tutorial

1. 打开文件 file (`Ctrl+O`)：直接打开一个文件并放入编辑器视图，但资源管理器 Explorer 视图中不会显示其路径位置等信息
2. 打开文件夹 folder (`Ctrl+K Ctrl+O`)：会将文件夹作为暂时的工作区，在资源管理器 Explorer 视图中会显示
3. 打开工作区 workspace：

4. 在 VSCode 中打开：文件 file、文件夹 folder、工作区 workspace，左侧资源管理器 Explorer 视图 view 中会显示项目的文件和文件夹. 当 VSCode 打开外部资源会弹出信任工作区 Workspace Trust 窗口询问是否允许该工作区在 VSCode 上运行
5. 用户界面 user interface：
    - 用活动栏 Activity Bar 在不同视图 view 之间切换，悬浮可以看视图名称以及快捷键 keyboard shortcut；
      当选择了活动栏的一个视图，就会在主侧栏 Primary Side Bar 中显示该视图的详细信息；
    - VSCode 用户界面的主要部分是编辑器 Editor，使用 `up`/`down` 导航建议，使用 `tab` 接收建议；
      同一个的编辑器可以有多个编辑器选项卡 Editor tab，被称为一个组 Group. 可以多开几个编辑器进行并排 side by side 编辑
    - 从面板 Panel 访问终端视图，使用 `` Ctrl+` `` 打开 VSCode 集成终端 integrated terminal，可以在不同 shell 之间选择；
    - 使用命令面板 Command Palette 访问命令，使用快捷键 `Ctrl+Shift+P` 可以快速打开；
      命令面板支持不同的操作模式，将开头的 `>` 删除则进入搜索模式.
6. 配置 VSCode 设置：使用 Setting Editor 可以修改设置，也可以直接修改 `setting.json`；按下 `Ctrl+,` 可以打开设置. `@modified` 可以显示被修改的设置项；设置范围从大到小分为用户设置、工作区设置、文件夹设置.
7. 编写代码：编写时会有智能提示补全 IntelliSense，对于有特殊 Code Action 时会有灯泡 lightbulb 图标，是对代码快速修复的建议，可以使用 `Ctrl+Space` 打开灯泡菜单. VSCode 内置了 HTML+CSS+JavaScript+TypeScript 等的支持，会有智能提示、语法突出、建议等功能.
8. 使用源代码管理：VSCode 集成了源代码控制管理 Source Control Management, SCM，默认在活动栏的源代码控制 Source Control 视图. 暂存 stage change + 提交 commit [+ 拉取 pull + 推送 push].
9. 安装语言拓展：在活动栏的拓展 Extensions 视图中可以浏览 Visual Studio Marketplace 并安装插件
10. 运行和调试代码：`F9` 设置断电，`F5` 启动调试或继续，可以在运行和调试 Run and Debug 视图中查看调试信息，还有监视变量、条件断点和启动配置.

#### 2.2&emsp;用户界面 User Interface

<!-- ---

### 3&emsp;用户指南

---

### 4&emsp;源控制 Source Control

---

### 5&emsp;终端 Terminal

---

### 6&emsp;语言 Languages

---

### 7&emsp;开发容器 Dev Containers

---

### 8&emsp;远程 Remote

---

### 9&emsp;数据科学 Data Science -->
