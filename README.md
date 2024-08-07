# Software_Engineering-HIT2024Fall

软件工程-2024秋季-刘铭班

笔者选用的cpp，但推荐使用Java

因为Lab3要做测试，老的评审工具checkstyle等都是基于java的

**Project选题为财务管理系统**

>开发一个财务管理系统，员工可以通过系统查询个人薪资等级和具体的工资，并能够实现按月、季度、年份进行工资的统计，以及通过系统提交财务报表，财务人员可以通过系统对不同用户的工资等级进行设置，管理员能够实现对不同用户权限的管理。

实际为工资管理系统，项目地址如下

采用的若依框架进行二次开发，难度不是很大，有机会笔者会把这个项目从零开始的配置文档写一下

```bash
git clone https://github.com/MayZyee/Financial_Management
```

**由不当使用此项目造成的课业危险由使用者自行承担！！笔者不负任何责任！！** 😇

**如发现问题请及时发issue反馈编写者以修正 同样也欢迎发issue或邮件探讨项目的设计**

- [Lab1](#结对编程与Git实战)
    - [Input](#Input)
    - [Make_Graph](#Make_Graph)
    - [Show_Graph](#Show_Graph)
        - [关于Graphviz](#关于Graphviz)
    - [Bridge_Words](#Bridge_Words)
    - [Generate_Text](#Generate_Text)
    - [Shortest_Path](#Shortest_Path)
    - [Random_Walk](#Random_Walk)
- [Lab2](#项目计划与原型设计)
- [Lab3](#代码评审与单元测试)
- [Lab4](#OO分析与设计)
- [Project](#Project)
- [更新日志](#更新日志)
## 结对编程与Git实战


如果能找到平替就无所谓了，或者Lab3再用Java写一份

在`Lab1`文件夹下，`lab1.cpp`文件为整合后的代码，等价于`main.cpp`+`read.cpp`+`graph.cpp`

若`main.cpp`+`read.cpp`+`graph.cpp`与`lab1.cpp`内容不同，请以`lab1.cpp`代码为准

**本实验的数据结构写的非常抽象**，请斟酌使用😅

### Input

在`read.cpp`中实现，其余全部功能都在`graph，cpp`中实现

用`fopen`打开文件，用`fgets`读取文件内容，存在`char`型的缓冲区`buffer`中

随后依次读入`buffer`中的字符，读到`a-z`直接连接到`processedLine`的结尾，如果是`A-Z`则需要进行大小写转化

由于读到其他字符，如`!@#$%^?`或空格回车等，都当成空格

于是当读到非`a-zA-Z`时，即为读到空格，需要判断一下`processedLine`是否为空

若非空，即上一个单词已经读完，将其`push_back`到`processedLines`里（注意，`processedLine`类型为`string`，而`processedLines`类型为`vector<string>`）

若`processedLine`为空，则说明是连续多个空格，则不进行`push_back`操作
最后返回的内容应为`vector<string>`类型的小写的单词表`processedLines`

### Make_Graph

由于上一部分已经实现了文本的读入，我们得到了一个有序的单词表

存储有向图的数据结构如下，应前文所说**非常抽象**

`unorder_map<string, int> nodes`用于定义顶点，前者存储节点名，即单词；后者为对应的顶点号，这里举例说明：

> 可近似理解：
>
> 若输入的文本为“hello world"
>
> 则有`nodes = {(hello,0), (world,1)}`
>
> 若输入为“hello world, hello reader”
>
> `nodes = {(hello,0), (world,1), (reader,2)}`
>
> 其本质为散列表，对于重复的节点不再新建，按单词名查找其顶点号

`vector<vector<pair<int, int>>> adj`用于定义邻接表，这里举例说明：

> 可近似理解：
>
> 其形式如下，代表`prve`节点的所有后继结点及其边的权重
>
> `adj[prve] = {(next1, weight1), (next2, weight2)...}`
>
> 设有向图为:
>
> A ──> B
>
> └─>C
>
> 则有    `nodes = {(A,1), (B,2), (C,3) }`
>
> 对于`adj[1]`，表示节点A所有的边及其权重
>
> `adj[1] = {(2, 1), (3,1)}`表示节点号为1的顶点所有遍及其权重，1—>2

随后是建表过程，将`i`位置和`i+1`位置的单词查找出对应序号邻接表即可

需要注意的是，权重默认设为1，权重增加的判断为：

> 令初始化 `j = i+1` ，随后判断`j`位置的单词与`i`位置相等，且`i+1`位置与相对
>
> 随后遍历至单词表结束即可
>
> 读者可以自行造句进行测试，这里可以提供一个例子以供思考：
>
> `two to two to two two`  意为 1:58--2:02时间段

### Show_Graph

代码中有两个函数提供了此功能

一个是`print()`函数，一个是`showDirectedGraph()`函数

前者是对邻接表进行简单的打印，后者调用了**Graphviz**导出png文件

建议仔细看看`print()`函数是如何实现对于`nodes`和`adj`进行遍历访问，方便对后续更多访问操作进行理解

#### 关于Graphviz

参考[一小时实践入门 Graphviz - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/644358139)

此处也可用mermaid语言，导出md文件即可，读者可自行选取生成图片的方法

### Bridge_Words

首先需要包含一些错误检查，如输入的`word1`与`word2`是否在单词表中等

另外还有一个标志位，来表示相应信息是否需要被打印

这关系到后面根据bridge word生成新文本的函数后面会提到，不多赘述

具体桥接词获取如下图说明：



```mermaid
graph LR
  subgraph prve/word1
    prve_name-->prve_num
  end
  subgraph middle
    middle_num---weight1
  end
  subgraph next/word2
   next_num---weight2
  end
  prve_num-->middle_num
  middle_num-->next_num
```

输入`word1`，得到后继节点号`middle_num`，随后遍历后继节点`middle_num`的后继节点得到`next_num`

最后比较`word2`对应的节点号与`next_num`是否相等，若相等，`middle_num`号所对应的单词即为桥接词

桥接词可能有很多个，遍历其后继的后继所有即可

### Generate_Text

这里我们需要调用`queryBridgeWords()`函数来进行查询桥接词，并返回新文本

显然，我们并不想要相关桥接词的打印，只要生成的新文本即可

所以在`queryBridgeWords()`参数中，默认的有标志位`if_print`为1

在`generateNewText()`中对其调用时，将其置为0即可不打印无用信息

对于本函数的实现，仍然是类似前面的处理，将输入的文本进行小写归一化后存为一个单词表

然后进行逐个输出，并查询当前输出单词与即将输出的单词之间是否有桥接词，若有，输出第一个即可

输出的单词存在另一个单词表中，作为结果返回

### Shortest_Path

最短路径问题，采用dijk算法，有合法性检查，同时也对输入一个单词或两个单词有不同的输出

即求两点间的最短路径或单点到其他所有点的最短路径

> 需要注意的是，此处将自身到自身的距离设为了0，或者自环的权重
>
> 对于非自环，但是仍有环路到自身的情况
>
> 如"end to end"，需要找去"end"的所有前驱
>
> 起点到其所有前驱的距离，加上这条边的距离维护最小值，即为非自环的最小值
>
> 如果同时出现自环与非自环，需要再次进行比较取最小

如果仍有不理解，建议重新看**Make_Graph**部分，并动手画图方便理解

### Random_Walk

用cpp内置随机函数，从单词表中选取一个作为起点，并对其后继边随机选取

设置一个二维数组标志位来判断是否有重复路径，此为终止条件

或者，若其没有后继，则终止

同时读取键盘输入信息，每次读入非'ESC'键，则前进一步

**此处更好的方法是采用thread开多线程**

但是解决线程异常可能会花费很多时间，笔者比较懒就没做这个

最后结果打印整个路径到终端，并写入文件，并返回路径顺序的单词表

## 项目计划与原型设计

选题为财务管理系统，要求如下

>开发一个财务管理系统，员工可以通过系统查询个人薪资等级和具体的工资，并能够实现按月、季度、年份进行工资的统计，以及通过系统提交财务报表，财务人员可以通过系统对不同用户的工资等级进行设置，管理员能够实现对不同用户权限的管理。

可以看出，实际为工资管理系统

具体根据指导书操作`PingCode`即可，在后续的迭代不会再要求使用`PingCode`

还要有一个录制视频作为演示，建议尽早启动项目

**敏捷宣言：♿我们将会很快做完♿**

**极限编程：😀ddl之前加班😀**

## 代码评审与单元测试

**注意，此处`Lab3/code/lab1，cpp`相较于`Lab1/lab1.cpp`有所改动，在进行Lab3实验时请以Lab3目录下的代码为准**

工具上，选用了**`Cpplint`**、**`Cppcheck`**与**`Cunit`**作为平替

简单来说

> `Cpplint`作为代码风格检查的工具
>
> `Cppcheck`作为代码静态检查工具，异常内存使用，释放检查；内存泄漏检查，主要是通过内存引用指针等问题
>
> `Cunit`作为单元测试
>
> 前两者不能完全作为老师提供的Java下测试工具的平替
>
> 但是只要能在报告上糊弄过去不就好了😀

详细的内容见报告，本次实验可以选择性验收，若不验收则分数仅以报告为参考

## OO分析与设计

针对**`Project`** 进行OO分析

徐汉川老师班好像有对ai检查

建议对结尾的问答重新写一下

## Project

两次汇报的PPT，具体的也不想多讲了，仅供参考

后续打算把项目的文档补全，详细教一下包括环境配置到成功启动一系列的操作

项目地址如下，采用的若依框架进行二次开发

```bash
git clone https://github.com/MayZyee/Financial_Management
```

## 更新日志

- 2024/7/4 补全Lab2、Lab3、Lab4的报告及project汇报

- 2024/6/?  修复了文本读入时，会将权重大于1的路径重复添加的Bug

- 2024/5/2- 修复了最短路径的Bug

- 2024/5/17 commit Lab1/lab1.cpp

- 2024/5/14 commit Lab1/
