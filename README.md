# Software_Engineering-HIT2024Fall

软件工程-2024秋季-刘铭班

### Lab 1：结对编程与Git实战

推荐使用Java，因为Lab3要做测试，老的评审工具checkstyle等都是基于java的

如果能找到平替就无所谓了，或者Lab3再用Java写一份

本实验的数据结构写的非常抽象，请斟酌使用

#### Input

在`read.cpp`中实现。用`fopen`打开文件，用`fgets`读取文件内容，存在`char`型的缓冲区`buffer`中。随后依次读入`buffer`中的字符，读到`a-z`直接连接到`processedLine`的结尾，如果是`A-Z`则需要进行大小写转化。由于读到其他字符，如`!@#$%^?`或空格回车等，都当成空格，于是当读到非`a-zA-Z`时，即为读到空格，需要判断一下`processedLine`是否为空。若非空，即上一个单词已经读完，将其`push_back`到`processedLines`里（注意，`processedLine`类型为`string`，而`processedLines`类型为`vector<string>`）。若`processedLine`为空，则说明是连续多个空格，则不进行`push_back`操作。
最后返回的内容应该为`vector<string>`类型的小写的单词表`processedLines`。
