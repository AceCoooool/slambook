#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <ceres/ceres.h>
#include <ceres/rotation.h>

using namespace std;
using namespace cv;


void find_feature_matches(
    const Mat &img_1, const Mat &img_2,
    std::vector<KeyPoint> &keypoints_1,
    std::vector<KeyPoint> &keypoints_2,
    std::vector<DMatch> &matches);

Point2d pixel2cam(const Point2d &p, const Mat &K);

struct PnPProblem {
    // 定义PnP结构体的接收数据: 2D点, 3D点, 相机内参
    PnPProblem(double x, double y, double X, double Y, double Z, double cx, double cy, double fx, double fy) :
        x_(x), y_(y), X_(X), Y_(Y), Z_(Z), cx_(cx), cy_(cy), fx_(fx), fy_(fy) {}
    // 定义函数模板, 模板参数为位姿和残差
    template<typename T>
    bool operator()(const T *const pose, T *residual) const {
        //3D点储存进p数组
        T p[3];
        p[0] = T(X_);
        p[1] = T(Y_);
        p[2] = T(Z_);

        //相机位姿旋转
        T r[3];
        r[0] = pose[0];
        r[1] = pose[1];
        r[2] = pose[2];

        //3D点旋转
        T newP[3];
        ceres::AngleAxisRotatePoint(r, p, newP);

        //3D点平移
        newP[0] += pose[3];
        newP[1] += pose[4];
        newP[2] += pose[5];

        //像素坐标系到相机坐标系映射
        T projectX = fx_ * newP[0] / newP[2] + cx_;
        T projectY = fy_ * newP[1] / newP[2] + cy_;

        //重投影后的残差
        residual[0] = T(x_) - projectX;
        residual[1] = T(y_) - projectY;

        return true;
    }

    double x_, y_;
    double X_, Y_, Z_;
    double cx_, cy_;
    double fx_, fy_;
};

void bundleAdjustmentCeres(const vector<Point3f> points_3d, const vector<Point2f> points_2d,
                           const Mat &K, Mat &R, Mat &t, Mat &T) {
    ceres::Problem problem;

    Mat rotateVector;
    Rodrigues(R, rotateVector);

    double pose[6];
    pose[0] = rotateVector.at<double>(0);
    pose[1] = rotateVector.at<double>(1);
    pose[2] = rotateVector.at<double>(2);
    pose[3] = t.at<double>(0);
    pose[4] = t.at<double>(1);
    pose[5] = t.at<double>(2);

    double fx = K.at<double>(0, 0);
    double fy = K.at<double>(1, 1);
    double cx = K.at<double>(0, 2);
    double cy = K.at<double>(1, 2);

    for (size_t i = 0; i < points_3d.size(); i++) {
        //残差二维, 待优化参数六维, 不使用核函数
        problem.AddResidualBlock(
            new ceres::AutoDiffCostFunction<PnPProblem, 2, 6>(new PnPProblem(
                points_2d[i].x, points_2d[i].y,
                points_3d[i].x, points_3d[i].y, points_3d[i].z,
                cx, cy,
                fx, fy
            )),
            nullptr,
            pose
        );
    }

    //使用QR求解
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    //输出优化信息到std::cout
    options.minimizer_progress_to_stdout = true;

    //开始优化求解
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    cout << summary.BriefReport() << endl;

    //输出坐标转化，由旋转向量转换为旋转矩阵
    rotateVector.at<double>(0) = pose[0];
    rotateVector.at<double>(1) = pose[1];
    rotateVector.at<double>(2) = pose[2];
    Rodrigues(rotateVector, R);

    t.at<double>(0) = pose[3];
    t.at<double>(1) = pose[4];
    t.at<double>(2) = pose[5];

    T = (Mat_<double>(3, 4) <<
                            R.at<double>(0, 0), R.at<double>(0, 1), R.at<double>(0, 2), t.at<double>(0),
        R.at<double>(1, 0), R.at<double>(1, 1), R.at<double>(1, 2), t.at<double>(1),
        R.at<double>(2, 0), R.at<double>(2, 1), R.at<double>(2, 2), t.at<double>(2)
    );
    cout << "优化后位姿参数T= " << endl << T << endl;
}


int main(int argc, char **argv) {
    if (argc != 5) {
        cout << "usage: pose_estimation_3d3d img1 img2 depth1 depth2" << endl;
        return 1;
    }
    //-- 读取图像
    Mat img_1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat img_2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);

    vector<KeyPoint> keypoints_1, keypoints_2;
    vector<DMatch> matches;
    find_feature_matches(img_1, img_2, keypoints_1, keypoints_2, matches);
    cout << "一共找到了" << matches.size() << "组匹配点" << endl;

    // 建立3D点
    Mat d1 = imread(argv[3], CV_LOAD_IMAGE_UNCHANGED);       // 深度图为16位无符号数, 单通道图像
    Mat K = (Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);
    vector<Point3f> pts_3d;
    vector<Point2f> pts_2d;
    for (DMatch m:matches) {
        // 获得匹配点的深度
        ushort d = d1.ptr<unsigned short>(int(keypoints_1[m.queryIdx].pt.y))[int(keypoints_1[m.queryIdx].pt.x)];
        if (d == 0)   // bad depth --- 舍弃深度为0的点
            continue;
        float dd = d / 5000.0;
        Point2d p1 = pixel2cam(keypoints_1[m.queryIdx].pt, K); // 像素坐标到相机坐标
        pts_3d.push_back(Point3f(p1.x * dd, p1.y * dd, dd));   // 物体的坐标(相机坐标系下 XYZ)
        pts_2d.push_back(keypoints_2[m.trainIdx].pt);
    }

    cout << "3d-2d pairs: " << pts_3d.size() << endl;

    // 这里暂时不考虑相机的畸变系数
    Mat r, t;
    solvePnP(pts_3d, pts_2d, K, Mat(), r, t, false, SOLVEPNP_EPNP); // 调用OpenCV 的 PnP 求解, 可选择EPNP, DLS等方法
    Mat R;
    cv::Rodrigues(r, R); // r为旋转向量形式, 用Rodrigues公式转换为矩阵

    cout << "R=" << endl << R << endl;
    cout << "t=" << endl << t << endl;

    Mat T;
    bundleAdjustmentCeres(pts_3d, pts_2d, K, R, t, T);
}


void find_feature_matches(const Mat &img_1, const Mat &img_2,
                          std::vector<KeyPoint> &keypoints_1,
                          std::vector<KeyPoint> &keypoints_2,
                          std::vector<DMatch> &matches) {
    //-- 初始化
    Mat descriptors_1, descriptors_2;
    // used in OpenCV3
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    // use this if you are in OpenCV2
    // Ptr<FeatureDetector> detector = FeatureDetector::create ( "ORB" );
    // Ptr<DescriptorExtractor> descriptor = DescriptorExtractor::create ( "ORB" );
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    //-- 第一步:检测 Oriented FAST 角点位置
    detector->detect(img_1, keypoints_1);
    detector->detect(img_2, keypoints_2);

    //-- 第二步:根据角点位置计算 BRIEF 描述子
    descriptor->compute(img_1, keypoints_1, descriptors_1);
    descriptor->compute(img_2, keypoints_2, descriptors_2);

    //-- 第三步:对两幅图像中的BRIEF描述子进行匹配，使用 Hamming 距离
    vector<DMatch> match;
    // BFMatcher matcher ( NORM_HAMMING );
    matcher->match(descriptors_1, descriptors_2, match);

    //-- 第四步:匹配点对筛选
    double min_dist = 10000, max_dist = 0;

    //找出所有匹配之间的最小距离和最大距离, 即是最相似的和最不相似的两组点之间的距离
    for (int i = 0; i < descriptors_1.rows; i++) {
        double dist = match[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist);
    printf("-- Min dist : %f \n", min_dist);

    //当描述子之间的距离大于两倍的最小距离时,即认为匹配有误.但有时候最小距离会非常小,设置一个经验值30作为下限.
    for (int i = 0; i < descriptors_1.rows; i++) {
        if (match[i].distance <= max(2 * min_dist, 30.0)) {
            matches.push_back(match[i]);
        }
    }
}

Point2d pixel2cam(const Point2d &p, const Mat &K) {
    return Point2d(
        (p.x - K.at<double>(0, 2)) / K.at<double>(0, 0),
        (p.y - K.at<double>(1, 2)) / K.at<double>(1, 1));
}
