# 库安装记录

### 1. Eigen

> 可以参考：[eigen安装](https://www.cnblogs.com/newneul/p/8256803.html)

#### ① 方式1（直接apt-get安装）

`sudo apt-get install libeigen3-dev`（友情提示：个人在Ubuntu16.04下面安装的不是最新版本）

> 比如遇到版本太老的bug，比如CUDA-9.0不支持。可以选择方式2

#### ② 方式2（官网下载安装）

1. 从[Eigen官网](http://eigen.tuxfamily.org/index.php?title=Main_Page)下载最新的版本（记录的时候最新版本是3.3.7）

2. 在下载的目录下面执行下述目录

   ```shell
   # 解压到/usr/include中
   sudo tar -xzvf eigen-eigen-323c052e1731.tar.gz -C /usr/include
   # 更改命名
   sudo mv /usr/include/eigen-eigen-323c052e1731 /usr/include/eigen3
   # 将Eigen及其子目录移动到include下面（个人觉得没必要）
   # sudo cp -r /usr/include/eigen3/Eigen /usr/include
   ```

检测版本的demo: 

```cpp
#include <iostream>
#include "Eigen/Dense"
using namespace std;

int main() {
    cout << "Eigen versions: " << endl;
    cout << EIGEN_WORLD_VERSION << "." << EIGEN_MAJOR_VERSION << "." << EIGEN_MINOR_VERSION << endl;
    return 0;
}
```

### 2. Pangolin

1. 从github上面下载：

   ```shell
   git clone https://github.com/stevenlovegrove/Pangolin.git
   ```

2. 安装依赖环境：

   ```shell
   sudo apt-get install libglew-dev
   ```

3. 编译：

   ```shell
   mkdir build
   cd build
   cmake ..
   make
   ```

   > 这里需要注意的是，如果当前系统环境采用的是`Anaconda`，那么可能会出现错误（一般是因为你可能`conda`安装过`libpng`，所以导致环境调用的是Anaconda下面的`libpng`）。最简单的方式是就是切换到`system`后再重新编译安装

