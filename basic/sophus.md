### 常用函数

- `Sophus::SO3 SO_R(R)`：利用旋转矩阵构造李群（但是需要注意，利用`cout`是以`so3`，即对应的李代数）
- `Eigen::Vector3d so3 = SO_R.log()`：返回李群对应的李代数
- `Sophus::SO3::exp(so3)`：返回李代数对应的李群
- `Sophus::SO3::hat(so3)`：返回李代数对应的反对称矩阵