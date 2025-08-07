---
title: Notes for Calculus Vol. I & II by Tom M. Apostol
author: Kur1su
contents:
  - One-variable calculus
  - Multi-variable calculus
  - Linear algebra
  - Applications to differential equations and probability
---

Learning Materials:

- *Calculus Vol. I*[^cal_i]
  [^cal_i]: [*Calculus Vol. I*](calculus_i(2nd).pdf)
- **Calculus Vol. II*[^cal_ii]
  [^cal_ii]: [*Calculus Vol. II*](calculus_ii(2nd).pdf)

Contents:

[toc]

---

## Preface and Introduction

There are two main points of view that what should constitute a first course in calculus and analytic geometry. Some people insist the way starting off with a logical, rigorous and theoretical development of the subject, while others argue that the course should stress applications of the calculus for engineers and physicists. This book represents an attempt to strike a sensible balance between the two. 对于微积分和解析几何的第一门课，有两种主要观点. 有些人认为，应该从逻辑、严谨和理论的发展开始，而另一些人则认为，微积分作为工程师和物理学家的一种工具，其课程应该强调微积分的应用. 这本书试图在这两者之间找到一个合理的平衡. (Page vii, para. 1, line 1-13[^cal_i])

Proofs of theorems are preceded by a geometric or intuitive discussion. The latter gives the student some insight into why they take a particular form and satisfies readers who are not interested in detailed proofs, while the complete proofs are also included for those who prefer a more rigorous presentation. 在定理或命题的证明之前，会有一个几何或直观的讨论. 后者使学生能够了解为什么定理或命题会以这样特定的形式出现，并满足那些对详细证明不感兴趣的读者，而完整的证明过程也在文中给出，以满足那些喜欢更严谨的表述的读者. (Page vii, para. 1, line 14-18[^cal_i])

The approach in this book has been suggested by the historical and philosophical development of calculus and analytic geometry, seeming unusual compared with other books. But it is definitely historically correct, pedagogically sound, and meaningful. 这本书中的处理方式是按照微积分和解析几何的历史和哲学发展来的，与其他书籍相比，似乎有些不寻常. 但它绝对在历史上是正确的，在教学中是有效的，并且是有意义的. (Page vii, para. 2[^cal_i])

The first two thirds of Volume I deals with the calculus of functions of one variable, including infinite series and an introduction to differential equations. The last third of Volume I introduces linear algebra with applications to geometry and analysis. It blends algebra and analysis and helps the transition from one-variable calculus to multi-variable calculus, discussed in the part 2 of Volume II. 卷 I 前三分之二讨论了一元函数的微积分，包括无穷级数和微分方程的介绍，后三分之一讨论了线性代数，包括几何和解析中的应用. 它将代数和解析有机地结合起来，有助于从一元微积分过渡到多元微积分，后者在卷 II 的第二部分讨论. (Page viii, para. 3[^cal_i])

Volume II is divided into three parts, entitled *Linear Analysis*, *Nonlinear Analysis*, and *Special Topics*. Part 1 contains an introduction to linear algebra. Part 2 discusses the calculus of functions of several variables. The special topics treated in Part 3 are *Probability* and *Numerical Analysis*. More details are given in the book. (Page vii, para. 2-5[^cal_ii])

### 1&emsp;Historical Introduction

历史介绍. This chapter includes:

- The two basic concepts of calculus 微积分学的两个基本概念
- Historical background 历史背景
- The method of exhaustion for the area of a parabolic segment 抛物线段面积的穷竭法
- A critical analysis of Archimedes' method 阿基米德方法的批判性分析
- The approach to calculus to be used in this book 本书中使用的微积分方法

### 2&emsp;Some Basic Concepts of the Theory of Sets

集合理论的基本概念. This chapter includes:

- Introduction to set theory 集合论简介
- Notations for designating sets 表示集合的符号
- Subsets 子集
- Unions, intersections, complements 并集，交集，补集

### 3&emsp;A Set of Axioms for the Real-Number System

实数系统的一组公理. This chapter includes:

- Introduction 简介
- The field axioms 域的公理
- The order axioms 序的公理
- Integers and rational numbers 整数和有理数
- Geometric interpretation of real numbers as points on a line 将实数从几何角度解释为直线上的点
- Upper bound of a set, maximum element, least upper bound (supremum) 集合的上界，最大元素，最小上界 (上确界)
- The least-upper-bound axiom (completeness axiom) 最小上界公理 (完备性公理)
- The Archimedean property of the real-number system 实数系统的阿基米德性质
- Fundamental properties of the supremum and infimum 上确界和下确界的根本性质
- *Existence of square roots of nonnegative real numbers 非负实数的平方根的存在性*
- *Roots of higher order. Rational powers 高阶根. 有理次幂*
- *Representation of real numbers by decimals 实数的小数表示*

### 4&emsp;Mathematical Induction, Summation Notation, and Related Topics

数学归纳法，求和符号，以及相关主题. This chapter includes:

- An example of a proof by mathematical induction 用数学归纳法的一个例子
- The principle of mathematical induction 数学归纳法原理
- *The well-ordering principle 良序原理*
- *Proof of the well-ordering principle 良序原理的证明*
- The summation notation 求和符号
- Absolute values and the triangle inequality 绝对值与三角不等式

---

## Part I&emsp;Fundamental Calculus

### 1&emsp;The Concepts of Integral Calculus

积分学的概念. This chapter includes:

- The basic ideas of Cartesian geometry 卡式几何的基本概念
- Functions. Informal description and examples 函数. 非正式描述与例子
- *Functions. Formal definition as a set of ordered pairs 函数. 作为有序对集合的正式定义*
- More examples of real functions 实函数的更多例子
- The concept of area as a set function 将面积作为集合函数的概念
- Intervals and ordinate sets 区间和坐标集
- Partitions and step functions 划分和阶梯函数
- Sum and product of step functions 阶梯函数的和与积
- The definition of the integral for step functions 阶梯函数的积分定义
- Properties of the integral of a step function 阶梯函数积分的性质
- Other notations for integrals 积分的其他表示法
- The integral of more general functions 更一般的函数的积分
- Upper and lower integrals 上积分与下积分
- The area of an ordinate set expressed as an integral 将坐标集面积表示为积分
- Informal remarks on the theory and technique of integration 积分理论和方法的不正式评论
- Monotonic and piecewise monotonic functions. Definition and examples 单调函数和分段单调函数. 定义与例子
- Integrability of bounded monotonic functions 有界单调函数的可积性
- Calculation of the integral of a bounded monotonic function 有界单调函数的积分计算
- Calculation of the integral $\int_a^bx^pdx$ when $p$ is a positive integer 当 $p$ 是正整数时，$\int_a^bx^pdx$ 的积分计算
- The basic properties of the integral 积分的基本性质
- Integration of polynomials 多项式的积分
- Proofs of the basic properties of the integral 积分基本性质的证明

### 2&emsp;Some Applications of Integration

积分的一些应用. This chapter includes:

- Introduction 简介
- The area of a region between two graphs expressed as an integral 两个曲线之间的区域面积积分
- Worked examples // TODO: what's worked examples?
- The trigonometric functions 三角函数
- Integration formulas for the sine and cosine 正弦和余弦的积分公式
- A geometric description of the sine and cosine functions 正弦和余弦函数的几何描述
- Polar coordinates 极坐标
- The integral for area in polar coordinates 极坐标下的面积积分
- Application of integration to the calculation of volume 积分在体积计算中的应用
- Application of integration to the concept of work // TODO: what's the concept of work?
- Average value of a function 函数的平均值
- The integral as a function of the upper limit. Indefinite integrals 积分上限的函数. 不定积分

### 3&emsp;Continuous Functions

连续函数. This chapter includes:

- Informal description of continuity 连续性的非正式描述
- The definition of the limit of a function 函数极限的定义
- The definition of continuity of a function 函数连续性的定义
- The basic limit theorems. More examples of continuous functions 基本极限定理. 更多的连续函数例子
- Proofs of the basic limit theorems 基本极限定理的证明
- Composite functions and continuity 复合函数和连续性
- Bolzano's theorem for continuous functions 连续函数的波尔查诺定理
- The intermediate-value theorem for continuous functions 连续函数的介质定理
- The process of inversion (函数的) 反转过程
- Properties of functions preserved by inversion 反转过程中保持的函数性质
- Inverses of piecewise monotonic functions 分段单调函数的反函数
- The extreme-value theorem for continuous functions 连续函数的极值定理
- The small-span theorem for continuous functions (uniform continuity) 连续函数的局部定理 (一致连续性)
- The integrability theorem for continuous functions 连续函数的可积性定理
- Mean-value theorems for integrals of continuous functions 连续函数积分的中值定理

### 4&emsp;Differential Calculus

微分学. This chapter includes:

- Historical introduction 历史介绍
- A problem involving velocity 涉及速度的问题
- The derivative of a function 函数的导数
- Examples of derivatives 导数的例子
- The algebra of derivatives 导数的代数
- Geometric interpretation of the derivative as a slope 导数作为斜率的几何解释
- Other notations for derivatives 导数的其他表示法
- The chain rule for differentiating composite functions 复合函数求导的链式法则
- Applications of the chain rule. Related rates and implicit differentiation 链式法则的应用. 相关速率和隐函数求导
- Applications of differentiation to extreme values of functions 函数极值求导的应用
- The mean-value theorem for derivatives 导数的中值定理
- Applications of the mean-value theorem to geometric properties of functions 中值定理在函数几何性质中的应用
- Second-derivative test for extrema 极值的二阶导数判别法
- Curve sketching 曲线作图
- Worked examples of extremum problems // TODO: what's worked examples?
- *Partial derivatives* 偏导数

### 5&emsp;The Relation between Integration and Differentiation

积分与微分的关系. This chapter includes:

- The derivative of an indefinite integral. The first fundamental theorem of calculus 不定积分的导数. 微积分第一基本定理
- The zero-derivative theorem 零导数定理
- Primitive functions and the second fundamental theorem of calculus 原函数和微积分第二基本定理
- Properties of a function deduced from properties of its derivative 从函数的导数性质推导出的函数性质
- The Leibniz notation for primitives 原函数的莱布尼兹记号
- Integration by substitution 换元积分法
- Integration by parts 分部积分法

---

## Part II&emsp;Advanced Calculus and Applications

### 6&emsp;The Logarithm, the Exponential, and the Inverse Trigonometric Functions

对数、指数和反三角函数

### 7&emsp;Polynomial Approximations to Functions

函数的多项式逼近

### 8&emsp;Introduction to Differential Equations

微分方程的介绍

### 9&emsp;Complex Numbers

复数

### 10&emsp;Sequences, Infinite Series, Improper Integrals

序列、无穷级数和瑕积分

### 11&emsp;Sequences and Series of Functions

函数的序列和级数

---

## Part III&emsp;Calculus in Analytic Geometry

### 12&emsp;Vector Algebra

向量代数

### 13&emsp;Applications of Vector Algebra to Analytic Geometry

向量代数在解析几何中的应用

### 14&emsp;Calculus of Vector-Valued Functions

向量值函数的微积分

---

## Part IV&emsp;Linear Analysis

### 15&emsp;Linear Spaces

线性空间

### 16&emsp;Linear Transformations and Matrices

线性变换和矩阵

### 17&emsp;Determinants

行列式

### 18&emsp;Elgenvalues and Eigenvectors

特征值和特征向量

### 19&emsp;Elgenvalues of Operators Acting on Euclidean Spaces

欧几里得空间上算子的特征值

### 20&emsp;Linear Differential Equations

线性微分方程

### 21&emsp;Systems of Differential Equations

微分方程组

---

## Part V&emsp;Nonlinear Analysis

### 22&emsp;Differential Calculus of Scalar and Vector Fields

标量和向量场的一阶微分学

### 23&emsp;Applications of the Differential Calculus

微分学的应用

### 24&emsp;Line Integrals

线积分

### 25&emsp;Multiple Integrals

多重积分

### 26&emsp;Surface Integrals

曲面积分

---

## Part VI&emsp;Special Topics

### 27&emsp;Set Functions and Elementary Probability

集合函数和基本概率

### 28&emsp;Calculus of Probabilities

概率的微积分

### 29&emsp;Introduction to Numerical Analysis

数值分析的介绍
