# 常用函数

## 图像IO

- `Mat cv::imread(const String& filename, int flag=IMREAD_COLOR)`：读取图片。其实的flag有下述一些

  - [cv::IMREAD_UNCHANGED](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80aeddd67043ed0df14f9d9a4e66d2b0708) = -1
  - [cv::IMREAD_GRAYSCALE](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80ae29981cfc153d3b0cef5c0daeedd2125) = 0, 
  - [cv::IMREAD_COLOR](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80af660544735200cbe942eea09232eb822) = 1, 
  - [cv::IMREAD_ANYDEPTH](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80a0b486c93c25e8a0b0712681bb7254c18) = 2, 
  - [cv::IMREAD_ANYCOLOR](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html#gga61d9b0126a3e57d9277ac48327799c80ab6573b69300c092b61800222fe555953) = 4, 
  - ...... （更多请参考：[官方文档](https://docs.opencv.org/3.4.5/d4/da8/group__imgcodecs.html)）

- `void cv::imshow(const String& winname, InputArray mat)`：显示图片，窗口名为winname

  > 需要注意的是，需要配合`cv.waitKey(int)`才能显示在屏幕上

- `int cv::waitKey(int delay=0)`：等待按键的时间，如果是0的代表一直显示（需要按键才会继续执行）。而比如25，则代表显示25ms



## 特征提取

大部分二维特征类都是继承自：`cv.Feature2D`，例如：



`cv.Feature2D`的一些公共方法（有些是在其子类实现）：

- `virtual void cv::Feature2D::detect(InputArray image, vector<KeyPoint>& keypoints, InputArray mask=noArray())`：检测image里面的特征点
- `virtual void cv::Feature2D::compute(InputArray image, vector<KeyPoint>& keypoints, OutputArray descriptors)`：计算描述子

### ORB特征（Oriented Fast and Rotated BRIEF）

- `static Ptr<ORB> cv::ORB::create(int features=500, float scaleFactor=1.2f, int nlevels=8, int edgeThreshold=31, int fisrtLevel=0, int WTA_K=2, scoreType=int ORB::HARRIS_SCORE, int patchSize=31, int fastThreshold=20)`：创建ORB"构造器"
  - features：最多保留的特征数目
  - scaleFactor：金字塔之间的"倍率"，比如`scaleFactor=1.2f`，代表下一层为前一层的 `(h/1.2)x(w/1.2)`
  - nlevels：金字塔层数，第k层的大小为：`(h/1.2^(k-firstLevel))x(w/1.2^(k-firstLevel))`
  - edgeThreshold：This is size of the border where the features are not detected. It should roughly match the patchSize parameter.
  - firstLevel：选择第几层作为第一层（即原始图片大小），比如选4，那么0-3层则比原始图更大
  - WTA_K：BRIEF描述子"进制数"，比如默认为2代表二进制描述子（采用0-1）
  - scoreType：特征排序方式，默认采用HARRIS算法
  - patchSize：oriented BRIEF描述子采用的patch大小

### SIFT

- `static Ptr<SIFT> cv::xfeatures2d::SIFT::create(int nfeatures=0, int nOctaveLayers=3, double contrastThreshold=0.04, double edgeThreshold=10, double signma=1.6)`：创建SIFT构造器
  - nfeatures：保留的特征数（选取最佳的nfeatures个）
  - nOctaveLayers：每一组包含的层数
  - contrastThreshold：对比度阈值，用于过滤掉弱对比度区域中的弱特征（记得该值越大，产生的特征数越少）
  - edgeThreshold：用于过滤掉类似边缘特征的阈值。其含义与constrastThreshold不同，edgeThreshold越大，保留的特征越多
  - sigma：第0层（octave0）上面高斯核对应的sigma。（如果使用图片质量较差，则可能需要降低该值）

### SURF

- `static Ptr<SURF> cv::xfeatures2d::SURF::create(double hessianThreshold=100, int nOctaves=4, int nOctaveLayers=3, bool extended=false, bool upright=false)`：创建SURF构造器
  - hessianThreshold：

### 绘制特征点

- `void cv::drawKeypoints(InputArray image, const std::vector<KeyPoint> &keypoints, InputOutputArray outImage, const Scalar& color=Scalar::all(-1), int flags=DrawMatchesFlags::DEFAULT)`：绘制特征点
  - image：图像
  - keypoints：从图像上获得的关键点
  - outImage：输出图像（具体输出的情况取决于flags）
  - color：关键点的颜色
  - flags：总共有下述四种（都是`DrawMatchesFlags::xxx`）
    - DEFAULT=0：输出图像会被created（即调用了Mat::create）--- 其实可以简单理解为会分配内存
    - DRAW_OVER_OUTIMG =1：输出图片不会被created --- 即不会调用分配内存，需要预先自己分配
    - NOT_DRAW_SINGLE_POINTS=2 ：单个关键点不会绘制
    - DRAW_RICH_KEYPOINTS =4：关键点大小和方向均会绘制

- `void cv::drawMatches(InputArray img1, const std::vector<KeyPoint>& keypoints1, InputArray img2, const std::vector<KeyPoint>& keypoints2, const std::vector<DMatch>& matches1to2, InputOutputArray outImg, )`