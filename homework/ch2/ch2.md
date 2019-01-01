## 习题2

### 1. 阅读文献[1]和[14]，你能看懂其中的内容吗？

文献：

【1】英文：[A survey of monocular simultaneous localization and mapping](http://tis.hrbeu.edu.cn/en/oa/darticle.aspx?type=view&id=20150401)； 中文：[基于单目视觉的同时定位与地图构建方法综述](http://www.cad.zju.edu.cn/home/gfzhang/projects/JCAD2016-SLAM-survey.pdf)

【14】英文：[Graph-based slam: A survey](http://robot.sia.cn/EN/10.3724/SP.J.1218.2013.00500#)； 中文：[基于图优化的同时定位与地图创建综述](http://robot.sia.cn/CN/10.3724/SP.J.1218.2013.00500)

> 注：个人没读

### 2. 阅读SLAM的综述文献，例如[9, 15-18]等。这些文献关于SLAM的看法与本书有何异同

【9】[Past, Present, and Future of Simultaneous Localization And Mapping: Towards the Robust-Perception Age](https://arxiv.org/abs/1606.05830)

【15】[Visual Simultaneous Localization and Mapping: A Survey](https://www.researchgate.net/publication/234081012_Visual_Simultaneous_Localization_and_Mapping_A_Survey)

【16】[Topological simultaneous localization and mapping: A survey](https://www.researchgate.net/publication/259754230_Topological_simultaneous_localization_and_mapping_A_survey)

【17】[Kalman Filter for Robot Vision: A Survey](https://ieeexplore.ieee.org/document/5985520)

【18】[Recent advances in simultaneous localization and map-building using computer vision](https://www.tandfonline.com/doi/abs/10.1163/156855307780132081)

> 注：个人没读

### 3. g++命令有那些参数？怎么填写参数可以更改生成的程序文件名？

> 下述来自[gcc编译器学习记录](https://github.com/guodongxiaren/LinuxTool/blob/master/gcc.md)，更多可以参考：[g++参数介绍](https://www.cnblogs.com/lidan/archive/2011/05/25/2239517.html)

直接在g++后面加上要编译的cpp语言源文件

```shell
g++ hello.cpp    # 例子
```

这种默认的情况下会生成一个名为`a.out`的可执行文件。

> 注意，在Linux系统下，后缀名真的不是很重要的事，甚至没有后缀名都可以。这些都没有关系，比如你写一个shell的脚本，其实加不加后缀都是可以运行的。此时后缀的目的是为了便于用户管理和区分文件而已。By the way，如果你执行`./hello.cpp`，那么系统会把它也当做shell脚本来运行，根本不管什么后缀。

#### -o

最常用的编译选项，用于指定要生成的可执行文件的名称。

```shell
g++ -o hello hello.cpp
```

需要体会的一点是：g++对于参数的位置无要求！比如也可以写作

```shell
g++ hello.cpp -o hello
```

惟一要注意的就是`-o`后面一定要紧跟要生成的可执行文件名。

> 编译出的可执行文件，在Windows下就是exe（executive）。但Linux下，后缀名无限制。一般不指定后缀就可以了。

#### -g

用于给生成的可执行文件加上调试信息，只有这样才可使用[gdb](https://github.com/guodongxiaren/LinuxTool/blob/master/gdb.md)调试。

```shell
g++ -g -o hello hello.cpp
```

同样参数`-g`的也可写在`hello.cpp`后面。

#### -c

终止链接器的运行，输出文件为汇编后的目标文件`*.o`

```shell
g++ -c hello.cpp
```

生成文件为`hello.o`

#### -O2

对源码进行优化，使编译出的程序，运行效率更高。注意是大写的英语字母`O`，不是阿拉伯数字`0`

```shell
g++ -O2 hello.cpp -o hello
# O`是Optimize之意。同样还有`O1`，但是优化效果不如`O2`，缺省是`O0
```

#### -D

给编译的源文件传递一个宏。

```shell
g++ a.cpp -DHELLO -DWORLD=10 
```

相当于：

```cpp
//在a.cpp中定义了
# define HELLO
# define WORLD 10
```

#### -E

只激活预处理,这个不生成文件,你需要把它重定向到一个输出文件里面。

```shell
# demo
g++ -E hello.cpp > pianoapan.txt   
g++ -E hello.cpp | more   
```

> 注：一个hello word 也要与处理成800行的代码  

#### -I

包含自定义头文件的路径

```shell
g++ hello.cpp -include /root/pianopan.h   
```

#### -S

生成汇编代码以.s为后缀。
默认是**AT&T**汇编语法，加选项**masm=intel**可生成**Intel**语法的汇编。

```shell
g++ -S -masm=intel test.cpp
```

#### 静态链接库

静态链接库是后缀名为.a的文件。它有多个后缀为你.o的目标文件组成。

使用`-c`参数可以使编译在链接前终止，所以生成的是源文件对应的目标文件。

```shell
g++ -c addvec.cpp multvec.cpp
ar rcs libvector.a addvec.o multvec.o
```

`ar`是archive档案的缩写。上面命令生成了`.a`的静态库文件，在链接时，要如下：

```shell
g++ -c main2.cpp
g++ -static -o p2 main2.o ./libvector.a
```

#### 动态链接库

后缀名为`.so`的是动态共享链接库文件，其中的s就是shared共享的意思，如下命令：

```shell
g++ -shared -fPIC -o libvector.so addvec.c multvec.c
g++ -o p2 main2.cpp ./libvector.so
```

完成了生成`.so`以及链接`.so`的操作。`-fPIC`指示生成与位置无关的代码。

### 4. 使用build文件夹来编译你的cmake工程，然后在Kdevelop中试试

略

### 5. 刻意在代码中添加一些语法错误，看看编译会生成什么样的信息。你能看懂g++的错误信息吗？

略

### 6. 如果忘了把库链接到可执行程序上，编译会报错吗？报什么样的错？

会报错。对函数未定义的引用

### 7. 阅读《cmake实践》，了解cmake的其他语法

下载链接：[cmake实践](http://file.ncnynl.com/ros/CMake%20Practice.pdf)（个人还是觉得遇到了再去查更好）

### 8. 完善hello SLAM小程序，把它做成一个小程序库，安装到本地硬盘中。然后，新建一个工程，使用find_package找这个库并调用

> 可以参考：[视觉SLAM十四讲—第二讲习题](https://blog.csdn.net/w_pebble/article/details/80090247)

TODO

### 9. 寻找其他cmake教学材料，深入了解cmake，例如[Cmake-tutorial](https://github.com/TheErk/Cmake-tutorial)

1. [CMake 入门实战](http://www.hahack.com/codes/cmake/)
2. [Cmake如何入门-知乎](https://www.zhihu.com/question/58949190)：基本去这里寻找资料吧 :smile:

### 10. 找到Kdevelop的官方网站，看看它还有哪些特性。你都用上了吗？

抱歉！个人用[CLion](https://www.jetbrains.com/clion/)

### 11. 如果在上一讲学习了Vim，请试试Kdevelop的Vim编辑功能

略