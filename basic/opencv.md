## 常用函数

### 图像IO

- `Mat cv::imread(const string& filename, int flag=IMREAD_COLOR)`：读取图片。其实的flag有下述一些
  - [cv::IMREAD_UNCHANGED](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80aeddd67043ed0df14f9d9a4e66d2b0708) = -1
  - [cv::IMREAD_GRAYSCALE](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80ae29981cfc153d3b0cef5c0daeedd2125) = 0, 
  - [cv::IMREAD_COLOR](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80af660544735200cbe942eea09232eb822) = 1, 
  - [cv::IMREAD_ANYDEPTH](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80a0b486c93c25e8a0b0712681bb7254c18) = 2, 
  - [cv::IMREAD_ANYCOLOR](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80ab6573b69300c092b61800222fe555953) = 4, 
  - ...... （更多请参考：[官方文档](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html)）
- 



### 特征提取

#### ORB特征（Oriented Fast and Rotated BRIEF）

- `static Ptr<ORB> cv::ORB::create(int features=500, float scaleFactor=1.2f, int nlevels=8, int edgeThreshold=31, int fisrtLevel=0, int WTA_K=2, int ORB::HARRIS_SCORE, int patchSize=31, int fastThreshold=20)`：创建ORB"构造器"
  - features：最多保留的特征数目
  - scaleFactor：金字塔之间的"倍率"，比如`scaleFactor=1.2f`，代表下一层为前一层的 `(h/1.2)x(w/1.2)`
  - nlevels：金字塔层数，第k层的大小为：`(h/1.2^(k-firstLevel))x(w/1.2^(k-firstLevel))`
  - edgeThreshold：
  - firstLevel：选择第几层作为第一层（即原始图片大小），比如选4，那么0-3层则比原始图更大
  - WTA_K：