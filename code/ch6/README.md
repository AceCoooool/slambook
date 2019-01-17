## Ceres

1. 安装依赖库

   ```shell
   sudo apt-get install liblapack-dev libsuitesparse-dev libcxsparse3.1.4 libgflags-dev libgoogle-glog-dev libgtest-dev
   ```

   > 注：这里安装的libcxsparse版本和书上不同（Ubuntu16.04找不到libcxsparse3.1.2）。关于版本可以通过下面两种方式寻找：
   >
   > 1. `sudo apt-get install libcxsparse`+`Tab`键来查看能够安装的版本（推荐）
   > 2. 在[网站上面](https://ubuntu.pkgs.org/16.04/ubuntu-main-amd64/libsuitesparse-dev_4.4.6-1_amd64.deb.html)查看能够下载的版本

2. 下载库

   ```shell
   git clone https://github.com/ceres-solver/ceres-solver.git
   ```

3. 安装

   ```shell
   cd ceres-solver
   mkdir build
   cd build
   cmake ..
   make -j4
   sudo make install
   ```

   > 头文件在`/usr/local/include/ceres`下面；库文件在`/usr/local/lib`下面


## g2o

1. 安装依赖库

   ```shell
   sudo apt-get install libqt4-dev qt4-qmake libqglviewer-dev libsuitesparse-dev libcxsparse3.1.4 libcholmod3.0.2
   ```

   > 这里的`libcxsparse3.1.4`在ceres中已经说明了， `libcholmod3.0.2`和书上略有区别（主要Ubuntu16.04上面找不到`libcholmod-dev`）

2. 下载库

   ```shell
   git clone https://github.com/RainerKuemmerle/g2o.git
   ```

   > 建议采用作者提供的版本。从github上面下载的会比作者提供的版本更高，所以如果采用github的代码则原书上面会存在一些bug

3. 安装

   ```shell
   cd g2o
   mkdir build
   cd build
   cmake ..
   make -j4
   sudo make install
   ```

   > 头文件在`/usr/local/g2o`下面；库文件在`/usr/local/lib`下面

