---
title: 总结的markdown知识点
---
[此为源码](https://github.com/smellyjun/code/what_is_markdown.md)

# 总结的markdown知识点（一级标题）

## 1.文本规则（二级标题，n级同理）

正文直接输入

*斜体*

**粗体** 

***粗斜体***

~~划去~~

分割线

---


换行要实际空一行
不然输出相当于没有换行


## 2.数据结构

### 1.无序表

`-`+' '，如下
- 无序列表 1
- 无序列表 2
  - 无序列表 3 

'-'加俩空格实现缩进

~~微信最多支持二级列表~~

## 2.有序表

数字+'.'+' '，如下

2. 有序列表 2
4. 有序列表 4
5. 有序列表 5

## 3.引用

'>'，如下

>我没有说过这句话。——周树人

## 4.链接

悄无声息的引入[我的GitHub链接](https://github.com/smellyjun)

## 5.图片

![我是图片描述](photo\miku-0.jpg "miku")

## 6.表格

|姓名|年龄|工作|
|:-|:-:|-:|
|小陈|18岁|是学生|
|陈什么峰|不到20|住南通大街|
|不为人知的|类成年体|上体育累的死去活来|

## 7.代码块

句内``反引号

such as  `return` this
~~Fuck English~~

单独```

```c++
//c++
cout<<error;//不同语言不同高亮
```

## 8.数学公式 ~~推荐现用现学~~（乱码自己学）

行内公式使用方法，$ J_\alpha(x) = \sum_{m=0}^\infty \frac{(-1)^m}{m! \Gamma (m + \alpha + 1)} {\left({ \frac{x}{2} }\right)}^{2m + \alpha} \text {，行内} $

块公式使用方法如下：

$$H(D_2) = -\left(\frac{2}{4}\log_2 \frac{2}{4} + \frac{2}{4}\log_2 \frac{2}{4}\right) = 1$$

矩阵：

$$
  \begin{pmatrix}
  1 & a_1 & a_1^2 & \cdots & a_1^n \\
  1 & a_2 & a_2^2 & \cdots & a_2^n \\
  \vdots & \vdots & \vdots & \ddots & \vdots \\
  1 & a_m & a_m^2 & \cdots & a_m^n \\
  \end{pmatrix}
$$

## 9.TOC,全称为 Table of Content，列出全部标题。

## 目录（#+name）只作用于目录以下
1. [Example1](#example)
2. [Example2](#6.表格)
3. [Example3](#third-example)

### Example
## Example2
# Third Example


## end
## 致谢
[MD官方教程](https://markdown.com.cn/basic-syntax/)

[GitHub+Hexo 搭建个人网站详细教程](https://zhuanlan.zhihu.com/p/26625249)

[bing](https://cn.bing.com/images/search?q=%E5%88%9D%E9%9F%B3%E6%9C%AA%E6%9D%A5%E8%89%B2%E5%9B%BE&go=%E6%90%9C%E7%B4%A2&qs=ds&form=QBIR&first=1&tsc=ImageBasicHover)
