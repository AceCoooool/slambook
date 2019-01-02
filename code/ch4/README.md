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