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

应用软件默认安装在 `C:\Users\<Username>\AppData\Local\Programs\Microsoft VS Code\S`.

可以通过 `code [options] [paths...]` 命令行启动 VSCode

VSCode 是建立在 Electron 和 Chromium 的网络栈功能之上的，因此 VSCode 用户可以获得 Google Chrome 中可用的许多网络支持.

VSCode 提供 [VSCode 在线网站](https://vscode.dev/)，可以直接通过在网站进行编辑.

---

### 2&emsp;入门 Start

#### 2.1&emsp;教程 Tutorial

##### 2.1.1&emsp;用户界面 User Interface

当第一次打开 VSCode 时，基本上会呈现以下的界面布局

![alt text](img/image.png)

主要分成下面几部分：

- **活动栏 (Activity Bar)**：默认处于最左侧，用于在不同**视图 (View)** 之间切换，鼠标悬浮时能看到视图名称以及快捷键 (keyboard shortcut).
  默认会拥有以下几个视图：
  - **资源管理器 (Explorer)(`Ctrl+Shift+E`)**：用于查看和管理项目中的文件和文件夹
  - **搜索 (Search)(`Ctrl+Shift+F`)**：用于通过名称或内容搜索文件和文件夹
  - **源代码管理 (Source Control)(`Ctrl+Shift+G`)**：用于查看和管理版本控制
  - **运行和调试 (Run and Debug)(`Ctrl+Shift+D`)**：用于运行和调试代码
  - **拓展 (Extensions)(`Ctrl+Shift+X`)**：用于安装和管理 VSCode 拓展插件 (plugin)
- **主侧栏 (Primary Side Bar)(`Ctrl+B`)**：紧挨着活动栏，当选择了活动栏的一个视图时，主侧栏上就会显示其具体信息.
- **编辑器 (Editor)**：用户界面的主要界面，用于编写代码. 一个文件对于一个**编辑器选项卡 (Editor tab)**，例如新打开 VSCode 都会显示的 *欢迎 (Welcome)* 编辑器.
- **面板 (Panel)(`Ctrl+J`)**：默认是隐藏在下侧，与活动栏和主侧栏作用类似，也是用于显示视图的信息.
  默认会拥有以下几个视图：
  - **问题 (Problems)(`Ctrl+Shift+M`)**：用于显示问题信息，会以不同级别显示，如提示 (hint)、信息 (info)、警告 (warning)、错误 (error).
  - **输出 (Output)(`Ctrl+Shift+U`)**：用于显示输出信息，例如运行和调试的输出信息.
  - **调试控制台 (Debug Console)(`Ctrl+Shift+Y`)**：用于通过调试对话窗显示调试信息.
  - **终端 (Terminal)(`` Ctrl+` ``)**：用于运行命令行命令，可以通过快捷键 `` Ctrl+Shift` `` 快速新建和打开 VSCode 的集成终端 (integrated terminal)，支持创建以及切换不同类型的 shell.
  
  ![alt text](img/video.gif)
- **命令面板 (Command Palette)(`Ctrl+Shift+P`)**：最上方的搜索栏，可以用于访问命令；
  命令面板支持不同的操作模式，将开头的 `>` 删除则进入搜索模式.

  ![alt text](img/video-1.gif)

  !!! todo 命令面板的所有操作模式

  !!! note VSCode 内的所有操作都可以在命令面板内找到，有部分操作有快捷键和 GUI.

##### 2.1.2&emsp;在 VSCode 内打开项目

VSCode 支持三种打开编辑的方式，在 *文件 (File)* 选项卡中可以找到：

1. 打开文件 (file) (`Ctrl+O`)：直接打开一个文件并放入编辑器视图，但资源管理器视图中不会显示其路径位置等信息
2. 打开文件夹 (folder) (`Ctrl+K Ctrl+O`)：会将文件夹作为暂时的工作区，在资源管理器视图中会显示该文件夹的具体内容.
3. 打开工作区 (workspace)：工作区是可以同时包含多个根目录作为项目的 VSCode 文件，以 `.code-workspace` 为后缀名，通过该特殊的结构，可以记录工作区独自的设置、插件等.

!!! warning 信任工作区 (Workspace Trust)
    当 VSCode 从外部打开资源时会弹出信任工作区窗口询问是否许该工作区在 VSCode 上运行，这在保护

##### 2.1.3&emsp;编写代码

在文件中编写时会有智能提示补全 (IntelliSense)，使用 `↑`/`↓` 可以上下选择建议，使用 `tab`/`enter` 接受建议

对于出错或可改进的代码，会有特殊的代码操作 (Code Action)，会以灯泡图标 (lightbulb) 显示，可以使用 `Ctrl+.` 打开灯泡菜单，选择建议的代码操作.

VSCode 内置了 HTML, CSS, JavaScript, TypeScript 等语言的支持，会有智能提示、语法突出、建议等功能.

![alt text](img/video-2.gif)

!!! todo VSCode 的所有内置语言

##### 2.1.4&emsp;运行和调试代码

在 *运行 (Run)* 选项卡中可以找到运行和调试的选项，或者使用快捷键 `F5` 调试，`Ctrl+F5` 运行，可以在运行和调试视图中查看调试信息，还有监视变量、条件断点和启动配置

对于调试，有以下功能及其快捷键可以使用：

- 在光标所在行设置或取消断点 (Toggle Breakpoint)(`F9`)，另外，在行数的左侧可以点击设置或取消断点
- 在行内设置断点 (Inline Breakpoint)(`Shift+F9`)，另外，可以在调试时在行内点击加入断点
- 继续调试 (Continue)(`F5`)

![alt text](img/video-3.gif)

##### 2.1.5&emsp;配置 VSCode 设置

VSCode 的设置默认在活动栏的最下方 *管理 (Manage) > 设置 (Setting)* 选项，使用 *设置编辑器 (Setting Editor)* 页面来管理设置，可以通过 `Ctrl+,` 快捷键打开.

VSCode 内的设置都是以 `settings.json` 文件保存的，有三种设置范围，从大到小为：

- 用户设置 (User Settings)：全局的设置，存储在 `C:\Users\<Username>\AppData\Roaming\Code\User\settings.json` 内.
- 工作区设置 (Workspace Settings)：当前工作区的设置，直接存储在工作区文件 `<Workspace>.code-workspace` 内.
- 文件夹设置 (Folder Settings)：当前打开文件夹的设置，存储在当前打开文件夹根目录的下的 `.vscode\settings.json` 文件内.
  
  !!! note 文件夹设置只有根目录下的 `.vscode` 文件夹有效
      值得注意的是，当想要对打开文件夹下的子目录单独设置是无法使用 `.vscode\settings.json` 实现的，VSCode 只会识别打开文件夹根目录下的 `.vscode\settings.json`，包括其他设置文件如 `launch.json` 等.
      要想对子目录也单独设置，需要使用 VSCode 工作区，将子目录添加到工作区文件 `<workspace>.code-workspace` 中的 `folder.path` 属性，可以在同一工作区内相对独立的设置多个文件夹.

当打开设置编辑器时，可以通过搜索筛选设置选项，或通过特殊符号如 `@modified` 查看修改过的设置选项.

!!! todo 其他筛选设置的方式和功能以及设置选项的搜索路径.

##### 2.1.6&emsp;使用源代码管理

VSCode 集成了**源代码控制管理 (Source Control Management, SCM)**，默认在活动栏的源代码控制视图.

在安装了 Git 之后就可以使用，VSCode 支持各种 git 操作的可视化，例如基本的 *暂存 (stage changes)* + *提交 (commit)* [+ *拉取 (pull)* + *推送 (push)*].

![alt text](img/image-11.png)

##### 2.1.7&emsp;安装拓展

在活动栏的拓展视图中可以浏览 Visual Studio Marketplace 并安装插件.

!!! tip 常用的插件
    - [Chinese (Simplified) (简体中文) Language Pack for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=MS-CEINTL.vscode-language-pack-zh-hans)：为 VSCode 提供中文界面
      ![alt text](img/image-1.png)
    - [Code Runner](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner)：支持多种语言的运行，可以直接运行文件或选中的代码（在有语言解释器、编译器的前提下）
      ![alt text](img/image-2.png)
    - [Code Spell Checker](https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker)：检测英文拼写
      ![alt text](img/image-3.png)
    - [Error Lens](https://marketplace.visualstudio.com/items?itemName=usernamehw.errorlens)：在编辑器中高亮显示错误和警告
      ![alt text](img/image-4.png)
    - [Git Graph](https://marketplace.visualstudio.com/items?itemName=mhutchie.git-graph)：提供可视化 git 历史的视图
      ![alt text](img/image-5.png)
    - [HyperScopes Booster](https://marketplace.visualstudio.com/items?itemName=yfzhao.hscopes-booster)：可定制化选中括号对内的高亮
      ![alt text](img/image-6.png)
    - [Material Icon Theme](https://marketplace.visualstudio.com/items?itemName=PKief.material-icon-theme)：提供了多种文件夹图标主题，能更好分清项目结构
      ![alt text](img/image-7.png)
    - [vscode-pdf](https://marketplace.visualstudio.com/items?itemName=tomoki1207.pdf)：支持在 VSCode 内查看 pdf 文件
      ![alt text](img/image-8.png)
    - [Remote - SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh)：为 VSCode 的远程开发提供更好的 SSH 支持
      ![alt text](img/image-9.png)
    - [CodeGeeX: AI Coding Assistant](https://marketplace.visualstudio.com/items?itemName=AMiner.codegeex)：AI 编程助手，Github Copilot 的免费平替版
      ![alt text](img/image-10.png)
    >
    VSCode 对插件有几个命令行界面的命令，通过
    - `code --list-extensions` 可以列出所有已安装的插件，列出的信息被称为拓展的 ID (ext-id)
    - `code --install-extension <ext-id | path>` 可以安装插件. -->

#### 2.2&emsp;用户界面 User Interface

1. 基本布局
    - 编辑器 Editor：主要区域、可以并排编辑，每个打开的文件被称为一个选项卡 Tabs
    - 菜单栏 Menu Bar：最上方的一栏 VSCode 基本操作的选项卡.
    - 活动栏 Activity Bar：位于左侧，用于切换主要视图
    - 主侧栏 Primary Side Bar：主要视图空间
    - 辅助侧栏 Secondary Side Bar：位于主侧栏的对面，额外的视图空间
    - 面板 Panel：编辑区域下方额外的视图空间
    - 状态栏 Status Bar：有关打开项目和编辑的文件的信息

    VSCode 的布局可以自定义，通过拖动改变视图位置，调整选择活动栏的位置
2. 并排编辑
    编辑区域 editor region 可以在水平和竖直方向上打开多个编辑器，每个编辑器内所有文件/选项卡 Tabs 被称为一个组 Group.
    有多种方式可以在打开编辑器的情况下，打开另一个编辑器进行并排编辑：
    - 按住 `Alt` 并点开资源管理器视图内的文件（在右侧打开）
    - 使用 `Ctrl+\` 将当前编辑器水平切分，在选中的编辑器的右上角也会有操作 UI *向右拆分编辑器 Split Editor Right*，按住 `Alt` 时会变成 *向下拆分编辑器 Split Editor Down*.
    - 在资源管理器视图中选中文件后按下 `Ctrl+Enter` 将在右侧编辑器内再打开
    - 使用 `Ctrl+P` 快速搜索打开文件时使用 `Ctrl+Enter` 将在右侧编辑器内打开
    - 直接拖动文件到编辑区域的任意位置

    !!! tip 分编辑器与组编辑时的快捷键
        当分编辑器时，可以通过 `Ctrl+1` ~ `Ctrl+8` 快速切换选中编辑器，对于编辑器对应组内选项卡的切换，可以通过 `Ctrl+Tab` 和 `Ctrl+Shift+Tab` 进行切换.

    使用 `Ctrl+K Ctrl+Shift+\` 可以在组内切分编辑器 Split Editor in Group，而无需新开一个组/编辑器.

    VSCoe 可以通过 `workbench.editor.openSideBySideDirection` 修改拆分编辑器的方向，默认是右侧.

    浮动窗口 floating windows：VSCode 支持将选中编辑器以独立的窗口显示，提供了两种基本的命令：*移动编辑器到新窗口 Move Editor to New Window* 和 *复制编辑器到新窗口 Copy Editor to New Window*.
    VSCode 通过主窗口创建的浮动窗口只包含命令面板、状态栏、编辑器区域.
3. 缩略图 MiniMap（代码大纲 code outline）
    位于编辑器的右侧，可以快速导航和理解代码. 若编辑器中有折叠标记 (folding markers)，如 `#region` 或 `MARK:` 在缩略图中会显示该标记，通过在设置中设置 `"editor.minimap.side": "left"` 或 `"editor.minimap.enabled": false` 分别可以将缩略图移至左侧或完全禁用.
4. 粘滞滚动 Sticky Scroll
    在编辑器顶部会显示当前嵌套范围的起始线，可以通过它快速跳转. VSCode 使用不同的模型（大纲模型 outline model、折叠提供模型 folding provider model、缩进模型 indentation model）来创建粘滞滚动标题，可以在设置中修改 `editor.stickyScroll.defaultModel` 来选择模型，默认是大纲模型.
    缩进指南 Indent Guide：编辑器会通过竖线 vertical lines 显示缩进层级，可以通过设置 `editor.guides.indentation` 为 `false` 来取消显示.
5. 面包屑 Breadcrumbs
    VSCode 在编辑器顶部会有一条导航栏 navigation bar，或称面包屑，来指示文件路径；若对当前文件类型有相应的符号语言支持，则会追踪到当前光标的位置.
    可以通过 *查看 View > 外观 Appearance > 切换痕迹导航 Toggle Breadcrumbs* 或使用命令 *查看 View: 切换导航路径 Toggle Breadcrumbs* 命令来禁用面包屑.
6. 资源管理器视图
    资源管理器视图下有几个好用的功能
    - *在侧边打开 Open to the Side* (`Ctrl+Enter`)
    - *打开方式... Open With...*
    - *在文件资源管理器中显示 Reveal in File Explorer* (`Shift+Alt+R`)
    - *在集成终端打开 Open in Integrated Terminal*
    - *在外部终端打开 Open in External Terminal*
    >
    - *选择以比较 Select for Compare* 以及 *与已选项目进行比较 Compare with Selected*
    >
    - *打开时间线 Open Timeline*
    >
    - *复制路径 Copy Path* (`Shift+Alt+C`)
    - *复制相对路径 Copy Relative Path* (`Ctrl+K Ctrl+Shift+C`)

    VSCode 会在资源管理器视图下默认隐藏一些文件夹，例如 `.git`，可以在 `files.exclude` 配置项中选择要隐藏的文件和文件夹.

    在资源管理器视图和**打开的编辑器 Open Editors** 视图下可以通过按住 `Ctrl` 进行多个单文件或按住 `Shift` 进行系列文件选择，当选择两个文件时，还会有 *比较已选择的项目 Compare Selected* 选项快速比较两者差异.
7. 大纲 Outline 视图
    是资源管理器视图底部的单独视图，有不同的排序模式（*排序 Sort By: 位置 Position / 名称 Name / 类别 Category*）、可选 *光标追踪 Follow Cursor*、*在输入时筛选 Filter on Type*，还会显示错误和警告. 在设置中通过输入 `outline.` 可以配置显示信息.
8. 时间线 Timeline 视图
    是资源管理器视图底部的单独视图，可以可视化文件历史记录，同时包含 Git 提交记录和本地事件，在过滤时间线 Filter Timeline 操作里可以选择包含 Git 历史记录和本地历史记录.
    本地历史记录的每个条目可以：
    - *与文件进行比较 Compare with File*
    - *与上一个版本比较 Compare with Previous*
    >
    - *选择以比较 Select for Compare* 以及 *与已选项目进行比较 Compare with Selected*
    >
    - *显示内容 Show Contents*
    - *恢复内容 Restore Contents*
    >
    - *在文件资源管理器中显示 Reveal in File Explorer*：会在 `C:\Users\<username>\AppData\Roaming\Code\User\History\<file_hash\>` 下打开该文件的所有历史，通过该文件夹下的 `entries.json` 记录.
    >
    - *重命名 Rename*：修改记录条目在时间线视图下显示的名称，默认是 *已保存文件 File Saved* 和 *撤销/重做 Undo / Redo*，通过重命名可以记录更加详细的信息.

    !!! tip 通过**本地记录 Local History 命令组**恢复删除的文件
        如果不小心删除了文件，可以通过命令 *本地历史记录 Local History: 查找要还原的条目 Find Entry to Restore* 恢复，这会显示有本地历史记录的所有文件及其条目.

    本地历史记录的配置在 `workbench.LocalHistory.` 下，包含：
    - `enabled` - 启用或禁用本地历史记录（默认：true）
    - `maxFileSize` - 创建本地历史记录条目时的文件大小限制（默认：256 kb）
    - `maxFileEntries` - 本地历史记录每个文件的条目数量限制（默认：50）
    - `exclude` - 排除在本地历史记录中的文件
    - `mergeWindow` - 将短时间内进一步的更改添加到本地文件历史记录中的最后一个条目的时间间隔（默认：10s）

    提交历史记录的每个条目可以：
    - *打开更改 Open Changes*：查看该文件在这次提交下的更改
    - *查看提交 View Commit*：查看该提交的详细信息，可能包含其他文件的信息
    >
    - *复制提交 ID Copy Commit ID*
    - *复制提交消息 Copy Commit Message*

    可以在 `git.timeline.date` 中选择显示提交日期或文件提交的日期
9. 视图 View
    处理资源管理器视图，VSCode 还包含**搜索 Search**、**源代码控制 Source Control**、**运行 Run**、**扩展 Extensions**、扩展自定义视图等，可以通过 *查看 View: 打开视图 Open View* 命令打开任何视图.
    任意视图都可以拖动来改变放置的布局位置和顺序，也可以通过右键选择隐藏某些视图.
10. 命令面板 Command Palette
    完全使用键盘控制 VSCode 的关键，通过 `Ctrl+Shift+P` 可以调出命令面板，这里包含了 VSCode 的所有操作，另外命令的调用是通过 `>` 前缀识别的，事实上命令面板还包含了其他操作：
    - `Ctrl+P` - 通过键入名称导航到文件或符号
    - `Ctrl+Tab` - 选择打开当前组的文件
    - `Ctrl+P` + `>` (`Ctrl+Shift+P`) - 调用 VSCode 命令
    - `Ctrl+P` + `@` (`Ctrl+Shift+O`) - 导航到文件中的特定符号
    - `Ctrl+P` + `:` (`Ctrl+G`) - 导航到文件中的特定行
    - `Ctrl+P` + `?` - 获取所有在命令面板中可运行的命令
11. 配置编辑器

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
