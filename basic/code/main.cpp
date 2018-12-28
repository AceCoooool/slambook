#include <iostream>
#include "Eigen/Dense"
using namespace std;

int main() {
    cout << "Eigen versions: " << endl;
    cout << EIGEN_WORLD_VERSION << "." << EIGEN_MAJOR_VERSION << "." << EIGEN_MINOR_VERSION << endl;
    return 0;
}