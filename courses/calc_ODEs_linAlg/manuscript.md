---
title: 考研数学二/数学竞赛笔记
author: 吴玉灿
content:
  - 一元函数微积分 Calc
  - 常微分方程 ODEs
  - 线性代数 LinAlg
---

## 第一部分&emsp;一元函数微积分 (Calculus of One Variable)

### 第0章&emsp;分析基础方法

#### 0.1&emsp;初等变形

#### 0.2&emsp;数列

##### 0.2.1&emsp;裂项求和

##### 0.2.2&emsp;递推式构造常数列求通项

##### 0.2.3&emsp;幂数列求和与伯努利数

问题起源于如何求幂数列 $\{1^p, 2^p, \cdots, n^p\}$ 的和，将幂数列用 $\{k^p\}_1^n$ 表示，即求 $S_p$.

> 1. <https://en.wikipedia.org/wiki/Faulhaber%27s_formula>
> 2. <https://en.wikipedia.org/wiki/Bernoulli_number#Bernoulli_numbers_and_the_Riemann_zeta_function>
> 3. <https://www.bilibili.com/video/BV1wW421A75k/?spm_id_from=333.999.0.0&vd_source=8801f3e4d0f4778e3d5e4110b67c5842>
> 4. <https://www.bilibili.com/video/BV1k94y1t7cU/?spm_id_from=333.337.search-card.all.click&vd_source=8801f3e4d0f4778e3d5e4110b67c5842>

**定理 (幂数列求和递推式)**&emsp;对于数列 $\{k^p\}_{1}^{n} = \{1^p, 2^p, \cdots, n^p\}\ (p\in\mathbb{N})$，记其前 $n$ 项求和为 $S_{n,p}$，有递推式

$$
\begin{aligned}
  & S_{n,0} = n \\
  & (n+1)^p - 1 = \sum\limits_{k=1}^{p}{\binom{p}{k}S_{n,p-k}} = \binom{p}{1}S_{n,p-1} + \binom{p}{2}S_{n,p-2} + \cdots + S_{n, 0} \\
  & S_{n,p} = \dfrac{1}{p+1}\left[(n+1)^{p+1} - 1 - \sum_{k=1}^{p}{\binom{p+1}{k+1}S_{n, p-k}}\right] \\
  & S_{n,p} = \dfrac{1}{p+1} \left[n^{p+1}-1 + \sum_{k=1}^{p}{\binom{p+1}{k+1}(n^{p-k}-S_{n,p-k})}\right] + n^p
\end{aligned}
$$

成立.

**证明**&emsp; `TODO`

1. $S_{n+1,p} = S_{n,p} + (n+1)^p$
2. $S_{n+1,p} = 1 + \sum\limits_{k=0}^{p}{\binom{p}{k}S_{n,k}} = 1 + \sum\limits_{k=0}^{p-1}{\binom{p}{k}S_{n,k}} + S_{n,p}$
3. $(n+1)^p = 1 + \sum\limits_{k=0}^{p-1}{\binom{p}{k}S_{n,k}} = 1 + \sum\limits_{k=0}^{p-2}{\binom{p}{k}}S_{n,k} + mS_{n,p-1}$

**证毕**.

**定理 (Faulhaber's formula) (冯哈伯公式: 幂数列求和公式)**&emsp;对于 $\forall p\in\mathbb{N}$，有

$$
\begin{aligned}
  \sum_{k=1}^{n}{k^p} &= 1^p + 2^p + \cdots + n^p \\
  &= \dfrac{1}{p+1}\sum_{k=0}^{p}{\binom{p+1}{k}B_i^+n^{p+1-k}}
\end{aligned}
$$

成立.

其中 $B_i^+$ 为 Bernoulli number (伯努利数).

**证明**&emsp; `TODO`

**证毕**.

#### 0.3&emsp;不等式

### 第1章&emsp;函数与极限

1. 不等式：
2. 恒等式/初等变形/初等运算：多项式自增累加、三角函数增角累加、组合数、数列裂项
3. 空间解的逆方程（解对应可以有哪些整系数方程）、拆分嵌套/复合函数：Ch1.1-e.g.5
4. 抽象函数方程求解：Ch1.1-e.g.3, **Ch1.1-e.g.4**
5. 极限算法：
   1. 数列极限：Ch1.2-e.g.7
   2. 初等变形法：Ch1.2-e.g.2, Ch1.2-e.g.8
   3. 重要极限、泰勒展开、等价无穷小：Ch1.1-e.g.2, Ch1.1-T3, Ch1.2-e.g.3, Ch1.2-e.g.4

### 第2章&emsp;一元函数微分学

### 第3章&emsp;一元函数积分学

&nbsp;

## 第二部分&emsp;常微分方程 (Ordinary Differential Equations)

### 第4章&emsp;常微分方程

&nbsp;

## 第三部分&emsp;线性代数 (Linear Algebra)

### 第5章&emsp;行列式与矩阵

### 第6章&emsp;线性方程组与向量空间

### 第7章&emsp;矩阵的相似变换

### 第8章&emsp;二次型
