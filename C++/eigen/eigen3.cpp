#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense> 

using namespace std;
using namespace Eigen;

int main(int argc, char **argv)
{
    // Eigen::Matrix<typename Scalar, Dynamic, Dynamic>
    // Eigen::Array<typename Scalar, Dynamic, Dynamic>
    //Matrix
    Eigen::MatrixXd  mat_x;
    Eigen::Matrix4Xi mat_4x;
    Eigen::MatrixX3f mat_x3;
    //Vector
    Eigen::VectorXd    vec_x;
    Eigen::RowVectorXd rvec_x;
    //Array
    Eigen::ArrayXXd arr_xx;
    Eigen::Array4Xd arr_4x;
    Eigen::ArrayX3d arr_x3;
    Eigen::ArrayXd  arr_x;

    Eigen::MatrixXd mat1(3, 3);     mat1 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "mat1 = \n" << mat1 << endl;
    mat1.resize(2, 2);              mat1 << 1, 2, 3, 4;
    cout << "mat1 = \n" << mat1 << endl;

    Eigen::ArrayXXd arr1;           arr1 = Eigen::ArrayXXd::Random(3, 5);
    cout << "arr1 = \n" << arr1 << endl;

// 1.数据类型只能是整形
// 2.定义矩阵时，行数和列数必须是确定的
// 3.初始化的行数和列数对应
// 4.更改行数和列数后，配合使用resize()  

    Eigen::MatrixXd resize_matrix;
    int num1 = 3, num2 = 2;
    resize_matrix.resize(num1, num1);
    resize_matrix << Eigen::MatrixXd::Zero(num1, num1);
    cout << "resize1:\n" << resize_matrix << endl;
    resize_matrix.resize(num2, num2);
    resize_matrix << Eigen::MatrixXd::Ones(num2, num2);
    cout << "reszie2:\n" << resize_matrix << endl;




    return 0;
}