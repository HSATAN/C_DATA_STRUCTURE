#include<stdio.h>
#include<stdlib.h>

/*
用fleury（弗罗来算法）找欧拉回路 
算法原理:
  Fleury算法：
   任取v0∈V(G)，令P0=v0；
设Pi=v0e1v1e2…ei vi已经行遍，按下面方法从中选取ei+1：
（a）ei+1与vi相关联；
（b）除非无别的边可供行遍，否则ei+1不应该为Gi=G-{e1,e2, …, ei}中的桥（所谓桥是一条删除后使连通图不再连通的边）；
（c）当（b）不能再进行时，算法停止。 
*/
