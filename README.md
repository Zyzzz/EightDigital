# EightDigital
 A* Algorithms to Solve Eight-digit Problem
## 题目大意
在3×3的棋盘上，摆有八个棋子，每个棋子上标有1至8的某一数字。棋盘中留有一个空格，空格用0来表示。空格周围的棋子可以移到空格中。要求解的问题是：给出一种初始布局（初始状态）和目标布局（为了使题目简单,设目标状态为123804765），找到一种最少步骤的移动方法，实现从初始布局到目标布局的转变。

![题目图解](https://img-blog.csdn.net/20180116201941897?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdTAxMjI4MzQ2MQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

## 结题思路
 使用A*算法寻路，代价函数F(x)现在状态到目标状态每个位置不同的数字个数加寻路深度。
