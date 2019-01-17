## 3. Sophus

1. 从github上面下载

   ```shell
   git clone https://github.com/strasdat/Sophus.git
   ```

2. 安装

   ```shell
   cd Sophus
   git checkout a621ff  # 切换到非模板分支
   mkdir build
   cd build
   cmake ..
   make
   ```

3. 使用

   ```shell
   cmake_minimum_required( VERSION 2.8 )
   project( useSophus )
   
   # 为使用 sophus，您需要使用find_package命令找到它
   find_package( Sophus REQUIRED )
   include_directories( ${Sophus_INCLUDE_DIRS} )
   
   add_executable( useSophus useSophus.cpp )
   target_link_libraries( useSophus ${Sophus_LIBRARIES} )
   ```

TODO：补充Sophus模板类版本的安装

### 常用函数

- `Sophus::SO3 SO_R(R)`：利用旋转矩阵构造李群（但是需要注意，利用`cout`是以`so3`，即对应的李代数）
- `Eigen::Vector3d so3 = SO_R.log()`：返回李群对应的李代数
- `Sophus::SO3::exp(so3)`：返回李代数对应的李群
- `Sophus::SO3::hat(so3)`：返回李代数对应的反对称矩阵