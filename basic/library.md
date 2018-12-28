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

