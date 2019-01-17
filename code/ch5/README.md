## 1. OpenCV

1. 安装依赖项：

   ```shell
   sudo apt-get install build-essential libgtk2.0-dev libvtk5-dev libjpeg-dev libtiff4-dev libjasper-dev libopenexr-dev libtbb-dev
   ```

   > 其实进一步安装一些依赖的话，可以参照下面（Options）：
   >
   > ```shell
   > sudo apt-get install build-essential
   > sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
   > sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev # 处理图像所需的包
   > sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
   > sudo apt-get install libxvidcore-dev libx264-dev # 处理视频所需的包
   > sudo apt-get install libatlas-base-dev gfortran # 优化opencv功能
   > sudo apt-get install ffmpeg  # 此项可以采用其他方式
   > ```
   >
   > 注：其中`ffmpeg`可以采用PPA方式安装（二选一）
   >
   > ```shell
   > sudo apt-add-repository ppa:mc3man/trusty-media
   > sudo apt-get update
   > sudo apt-get install ffmpeg
   > ```

2. 下载opencv
   可以直接从官网下载：[OpenCV-release](https://opencv.org/releases.html)，选择3.4.5 from sources

3. 安装

   ```shell
   cd opencv-3.4.5
   mkdir build
   cd build
   cmake -D WITH_VTK=ON ..
   make -j4
   sudo make install
   ```

> 这里稍微需注意一下，请注意当前python的环境，因为有时候我们会在conda里面装了opencv，所以最好切换到系统的python下面

## 2. PCL

### Ubuntu14.04

```shell
sudo add-apt-repository ppa:v-launchpad-jochen-sprickerhof-de/pcl
sudo apt-get update
sudo apt-get install libpcl-all
```

> 安装完后，头文件位于`/usr/include/pcl-1.7`，库文件位于`/usr/lib`下面

### Ubuntu16.04（个人采用）

```shell
sudo apt-get install libpcl-dev
sudo apt-get install libproj-dev
sudo apt-get install pcl-tools
```

如果生成了`xx.pcd`文件，可以采用：

```shell
pcl_viewer xx.pcd
```

即可查看点云图



