#include <iostream>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/core/optimization_algorithm_dogleg.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <Eigen/Core>
#include <opencv2/core/core.hpp>
#include <cmath>
#include <chrono>
using namespace std;

// 曲线模型的顶点   模板参数: 优化变量维度和数据类型(_estimate就为此处的数据类型)
class CurveFittingVertex : public g2o::BaseVertex<2, Eigen::Vector2d> {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    virtual void setToOriginImpl() {               // 重置
        _estimate << 0, 0;
    }

    virtual void oplusImpl(const double *update) { // 更新
        _estimate += Eigen::Vector2d(update);
    }
    // 存盘和读盘：留空
    virtual bool read(istream &in) {}
    virtual bool write(ostream &out) const {}
};

// 误差模型    模板参数: 观测值维度, 类型, 连接顶点类型
class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex> {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    CurveFittingEdge(double x) : BaseUnaryEdge(), _x(x) {}
    // 计算曲线模型误差
    void computeError() {
        // _vertices为顶点类型, 由上述连接顶点类型所确定
        const CurveFittingVertex *v = static_cast<const CurveFittingVertex *> (_vertices[0]);
        const Eigen::Vector2d ab = v->estimate();
        _error(0, 0) = _measurement - std::sin(ab(0, 0) * _x + ab(1, 0));
    }
    virtual bool read(istream &in) {}
    virtual bool write(ostream &out) const {}
public:
    double _x;  // x值, y值为_measurement
};

int main(int argc, char **argv) {
    double a = 2.0, b = 0.1;                  // 真实参数值
    int N = 100;                              // 数据点
    double w_sigma = 0.1;                     // 噪声Sigma值
    cv::RNG rng;                              // OpenCV随机数产生器

    vector<double> x_data, y_data;            // 数据

    cout << "generating data: " << endl;
    for (int i = 0; i < N; i++) {
        double x = i / 100.0;
        x_data.push_back(x);
        y_data.push_back(
            sin(a * x + b) + rng.gaussian(w_sigma)
        );
        cout << x_data[i] << " " << y_data[i] << endl;
    }

    // 构建图优化, 先设定g2o
    typedef g2o::BlockSolver<g2o::BlockSolverTraits<2, 1> > Block;  // 每个误差项优化变量维度为3, 误差值维度为1
    Block::LinearSolverType *linearSolver = new g2o::LinearSolverDense<Block::PoseMatrixType>(); // 线性方程求解器
    Block *solver_ptr = new Block(linearSolver);                    // 矩阵块求解器
    // 梯度下降方法, 从GN, LM, DogLeg 中选
    g2o::OptimizationAlgorithmLevenberg *solver = new g2o::OptimizationAlgorithmLevenberg(solver_ptr);
    // g2o::OptimizationAlgorithmGaussNewton* solver = new g2o::OptimizationAlgorithmGaussNewton( solver_ptr );
    // g2o::OptimizationAlgorithmDogleg* solver = new g2o::OptimizationAlgorithmDogleg( solver_ptr );
    g2o::SparseOptimizer optimizer;     // 图模型
    optimizer.setAlgorithm(solver);     // 设置求解器
    optimizer.setVerbose(true);         // 打开调试输出

    // 往图中增加顶点
    CurveFittingVertex *v = new CurveFittingVertex();
    v->setEstimate(Eigen::Vector2d(0, 0));
    v->setId(0);
    optimizer.addVertex(v);

    // 往图中增加边
    for (int i = 0; i < N; i++) {
        CurveFittingEdge *edge = new CurveFittingEdge(x_data[i]);
        edge->setId(i);
        edge->setVertex(0, v);                // 设置连接的顶点
        edge->setMeasurement(y_data[i]);      // 观测数值
//        edge->setInformation(Eigen::Matrix<double, 1, 1>::Identity() * 1 / (w_sigma * w_sigma)); // 信息矩阵：协方差矩阵之逆
        edge->setInformation(Eigen::Matrix<double, 1, 1>::Identity());
        optimizer.addEdge(edge);
    }

    // 执行优化
    cout << "start optimization" << endl;
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    optimizer.initializeOptimization();
    optimizer.optimize(100);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

    // 输出优化值
    Eigen::Vector2d ab_estimate = v->estimate();
    cout << "estimated model: " << ab_estimate.transpose() << endl;

    return 0;
}
