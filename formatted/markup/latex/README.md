---
title: learn Latex
---

## latex的基本使用

### 基本概念

#### 命令

1. latex 中字母形式命令忽略其后的所有连续空格，可以接上 $\verb|{}|$ 或 $\verb*|\ |$ 使命令后出现空格.

    ```latex
    Shall we call ourselves \TeX users or \TeX{} users?
    ```
  
    > $\text{Shall we call ourselves \TeX users or \TeX{} users?}$\
2. 有些命令（如 $\verb|\bfseries|$）会对其后所有内容产生作用，使用一对花括号 $\verb|{\bfseries ...}|$ 作为分组限制. 环境则隐含了一个分组.
3. 个别命令在分组内仍会产生全局作用，如 $\verb|\setcounter|$ 等命令.

#### 文档类

$
\verb|\documentclass[| \langle options \rangle \verb|]{| \langle class \verb|-| name \rangle \verb|}|
$

其中 $\langle class \verb|-| name \rangle$ 为：

- $\verb|article|/\verb|ctexart|$ 文章格式
  常用于科技论文、期刊、报告、说明文档等简短文章；
  默认单面排版，默认标题不单独成页；无法使用 $\verb|\chapter|$ 命令；
  英文排版 $\verb|\part|$ 命令生成 $\text{``Part I''}$ 和 $\text{``}\langle part \verb|-| name \rangle\text{''}$ 靠左两行，不单独起页；中文排版生成 $\text{``第一部分}\quad\langle part\verb|-|name \rangle\text{''}$ 居中，不单独起页；
  英文排版页码在页尾中，无页眉；中文排版页码在页眉右，页眉左为节编号和节名称，标题页同英文排版；
- $\verb|report|/\verb|ctexrep|$ 长篇报告
  具有章节结构，用于综述、长篇论文（如毕业论文、硕士论文）、简单的书籍；
  默认单面排版，新章节 $\verb|\chapter|$ 紧跟上一页开始新一页，默认标题单独成页；
  $\verb|\part|$ 命令生成 $\text{``Part I''}/\text{``第一部分''}$ 和 $\text{``}\langle part \verb|-| name \rangle\text{''}$ 居中两行，单独成页；
  英文排版页码在页尾中，无页眉；中文排版页码在页眉右，页眉左为 $\text{``第一章}\quad\langle chapter \verb|-| name \rangle\text{''}$，章节页无页眉，页码在页尾中；标题页均是不计数无页码；
- $\verb|book|/\verb|ctexbook|$ 书籍
  包含章节结构和前言、正文、后记等结构，用于书籍；
  默认双面排版，新章节 $\verb|\chapter|$ 在奇数页（右侧页）开始，默认标题单独成页；
  英文排版页码在
