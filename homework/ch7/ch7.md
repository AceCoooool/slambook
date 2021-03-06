## 习题7

> 下述内容主要来自：[CSDN](https://blog.csdn.net/qq_17032807/article/details/84994607)（基本上全来自此blog，作者的名字真的是...，明明是大神）

### 1. 除了本书介绍的 ORB 特征点外,你还能找到哪些其他的特征点?请说说 SIFT 或SURF 的原理,对比它们与 ORB 之间的优劣。

除了ORB特征点之外，一般还有SIFT，SURF，BRISK，AKAZE等特征点。（注：这些特征在OpenCV里面均已实现）

- SIFT：又称为尺度不变特征转换(Scale-invariant feature transform），大致方法是首先搜索所有尺度下图像的位置，通过高斯微分函数来识别潜在的对于尺度和旋转不变的兴趣点，然后在候选位置通过拟合精细的模型来确定位置和尺度，再基于图像梯度，分配给关键点一个或多个方向，最后在每个关键点的周围邻域，在选定的尺度下测量图像局部梯度来描述关键点。
- SURF：又称为加速稳健特征（Speeded Up Robust Features)，其方法和构建图像金字塔的方法相反，其主要方法是通过修改滤波器的尺寸和模糊度从而得到不同层级的影像，但是寻找特征点的方法和SIFT类似。

SIFT和SURF能够比较稳定地提供较高的准确率，其中SIFT比SURF更准确一点，但是二者都特别慢。相较而言，ORB速度更快，但是更容易出现问题，而且错误率远比其他二者大。

#### ① SIFT

> 参考：[SIFT](https://my.oschina.net/abcijkxyz/blog/787662)



### 2. 设计程序,调用 OpenCV 中的其他种类特征点。统计在提取 1000 个特征点时,在你的机器上所用的时间。




### 3. (*) 我们发现 OpenCV 提供的 ORB 特征点,在图像当中分布不够均匀。你是否能够找到或提出让特征点分布更加均匀的方法?



### 4. 研究 FLANN 为何能够快速处理匹配问题。除了 FLANN 之外,还能哪些可以加速匹配的手段?

FLANN的全称为Fast Library for Approximate Nearest Neighbors，也就是快速近似最近邻。它是一个对大数据集和高维特征进行最近邻的算法的集合。在面对大数据集时它的性能要好于BFMatcher（暴力匹配）。匹配问题实际上就是一个特征向量求相似度问题。最简单的办法，就是逐个匹配对计算距离。明显这种遍历的方式是效率极低的，对于大数据情况下不适用。因此经典kd-tree的搜索回溯的搜索办法在这里派上了用场，减少了不必要的计算过程，提高了效率，但是对于多维数据而言，其效果往往不升反降。在经典kd-tree算法上提出了随机kd-tree算法，随机选出方差较大的维度，建立kd-tree，再进行搜索回溯。还有一种分级k-means tree，与之前不同的是先通过k-means算法（之后回环检测时会用到）来进行数据聚类，然后再进行kd-tree的建立。这些方法相交于传统的直接匹配法优势都比较大。（关于算法的具体实现可以参考：[KD-Tree算法原理](https://www.cnblogs.com/lysuns/articles/4710712.html)）

一般加速匹配的算法都是在经典的SIFT算法中使用，常见的有主成分分析法，将SIFT描述子从128维降到36维，从而匹配速度增加3倍多；或者用GPU加速，可以使得匹配速度提高十多倍；再后来就是用FPGA加速，其匹配速度能提升10倍；再后来的VF-SIFT（very fast SIFT）算法，其核心思想是从SIFT特征中提取4个特征角，根据特征角区间的不同，避免了大量不必要的搜索，这样据说是普通搜索的1250倍。

### 5. 把演示程序使用的 EPnP 改成其他 PnP 方法,并研究它们的工作原理。

目前除了EPnP外，OpenCV还提供了另外两种方法：迭代法和P3P法，此外，在OpenCV3中还另外提供了DLS法和UPnP法。首先，再明确一下PnP是啥。PnP，全称Perspective-n-Point，描述了当知道n个3D空间点及其投影位置时，如何估计相机的位姿。

EPnP（Efficient PnP）的思路是将空间中的任意3D点可以用4个不共面的3D点加权表示，然后通过n个3D点在相机平面的投影关系以及四个控制点的权重关系构建一个的矩阵，求这个矩阵的特征向量，就可以得到这个相机平面的坐标，再用POSIT正交投影变换算法得到相机位姿。

迭代法实质是迭代求出重投影误差的最小解先用DLT直接线性变换求解，然后用LM算法进行优化，这个解显然不是正解，而且这个方法只能使用4个共面特征点才能求得。

P3P法，它需要3对3D-2D的匹配点，然后通过三角形投影关系得到的方程组，然后将方程组进行变换得到两个二元二次方程进行求解。

DLS（Direct Least-Squares）算法整体思路是首先对PnP非线性最小贰乘建模，重新定义LS模型以便于参数降维然后构造Maculy矩阵进行求解，将PnP问题重构为无约束LSM问题然后优化求解。

UPnP（Uncalibrated PnP）算法跟EPnP差不了太多，仅仅是多估计了焦距。因此，比较适合未标定场合。

> TODO：自己看下各个算法的原理

### 6. 在 PnP 优化中,将第一个相机的观测也考虑进来,程序应如何书写?最后结果会有何变化?

考虑相机的观测，相当于加入了固定的顶点：即采用$T=I$矩阵

不考虑第一个相机观测的预测结果：

```json
T=
  0.997766 -0.0519786  0.0419744  -0.130482
 0.0507655   0.998276  0.0294683 -0.0106118
-0.0434338 -0.0272717   0.998684  0.0593671
         0          0          0          1
```

考虑第一个相机观测的预测结果：

```json
T2=
  0.997744 -0.0519595  0.0425126  -0.129974
 0.0505136    0.99813  0.0344081 -0.0185608
 -0.044221  -0.032183   0.998503  0.0392645
         0          0          0          1
```

可以发现结果还是有一些变化的。相当于添加了新约束：限制3D点尽可能在第一个相机构成的射线上面。

### 7. 在 ICP 程序中,将空间点也作为优化变量考虑进来,程序应如何书写?最后结果会有何变化?

即假设第二幅图像+深度信息所构成的3D坐标信息也是优化目标（即假定其并不一定准确），那么此时定义的边就应该是一个二元边（继承自：`g2o::BaseBinaryEdge`）而不是一元边（继承自：`g2o::BaseUnaryEdge`）

对比两者的结果

① 不考虑空间点：

```json
T=
   0.997207   0.0583427   -0.046639    0.137988
 -0.0578775     0.99826   0.0112663   -0.065517
  0.0472151 -0.00853546    0.998848  -0.0298169
          0           0           0           1
```

② 考虑空间点：

```json
T=
    0.99721   0.0558036  -0.0495865    0.143515
 -0.0556454     0.99844  0.00456704   -0.054681
   0.049764 -0.00179504    0.998759  -0.0282425
          0           0           0           1
```


### 8. (*) 在特征点匹配过程中,不可避免地会遇到误匹配的情况。如果我们把错误匹配输入到 PnP 或 ICP 中,会发生怎样的情况?你能想到哪些避免误匹配的方法?

目前书中用的是根据汉明距离的暴力匹配方法，然后根据经验参数（30或者是最小距离的两倍）根据其距离对匹配进行筛选。如果误匹配情况输入到PnP或是ICP中，再加上迭代算法选择不正确，初值估计不准确，就很容易导致计算结果产生误差，更有甚者会让迭代过程不稳定，甚至报错。目前比较流行的避免误匹配方法有：交叉匹配（在暴力匹配的基础上再匹配一次，如果两次结果一致，则认为是个特征点，如果不一致则滤掉，`BFMatcher XX (NORM_HAMMING, true)` ）、KNN匹配（K邻近匹配，匹配时候选择K个与特征点相似的点，一般K是2，如果区别足够大，则选择最相似的点作为匹配点，`bfMatcher->knnMatch(descriptors1, descriptors2, knnMatches, 2)` ）、RANSAC（随机采样一致性，利用两个图像之间的单应矩阵，根据重投影误差判定某个匹配是不是正确匹配，`findHomography`）等等，一般可以跟觉已有的成熟框架如ORB_SLAM2等等观察其对于不同场景所采取的避免误匹配的方法。同样，对于后端，在优化时可以用Huber损失函数等等增强优化算法的鲁棒性。

### 9. (*) 使用 Sophus 的 SE3 类,自己设计 g2o 的节点与边,实现 PnP 和 ICP 的优化。

TODO

### 10. (*) 在 Ceres 中实现 PnP 和 ICP 的优化。

其实具体的实现和第6章采用的方式没有大不同。

PnP的结果如下：

```json
[0.9979193235018684, -0.05138614184164847, 0.03894211355593457, -0.125586888334431;
 0.05033847638510064, 0.9983556582068486, 0.0274229378731877, -0.007363635617851583;
 -0.04028723838636725, -0.02540559294722387, 0.9988651031396582, 0.06099929096153322]
```

可以发现和上述G2O得到的结果还是比较接近的。

> ```json
> T=  // G2O
>   0.997766 -0.0519786  0.0419744  -0.130482
>  0.0507655   0.998276  0.0294683 -0.0106118
> -0.0434338 -0.0272717   0.998684  0.0593671
>          0          0          0          1
> ```

ICP的结果如下：

```json
[0.997206564871252, 0.05834273264213675, -0.04663895931006042, 0.1379879639364653;
 -0.05787745374349845, 0.9982601222918902, 0.01126625891543577, -0.06551699902642329;
 0.04721511755620776, -0.008535443141898899, 0.9988482762084164, -0.02981649372255712]
```

可以发现和上述G2O得到的结果也是比较接近的。

> ```json
> T=   // G2O
>    0.997207   0.0583427   -0.046639    0.137988
>  -0.0578775     0.99826   0.0112663   -0.065517
>   0.0472151 -0.00853546    0.998848  -0.0298169
>           0           0           0           1
> ```

感觉Ceres写起来更简单一些～