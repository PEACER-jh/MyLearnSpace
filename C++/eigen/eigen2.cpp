#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense> 

using namespace std;
using namespace Eigen;

int main(int argc, char **argv)
{
    //矩阵/数组的初始化赋值
    Eigen::Vector3d v1(1, 1, 1);     //C++11之前的版本
    cout << "v1 = " << v1.transpose() << endl;
    Eigen::VectorXd v2(3);           //对于动态矩阵，()中表示的是矩阵的尺寸
    v2 << 2, 2, 2;
    cout << "v2 = " << v2.transpose() << endl;
    Eigen::MatrixXd mat_xd(2, 3);
    mat_xd << 1, 2, 3, 4, 5, 6;
    cout << "mat_xd\n" << mat_xd << endl;
    /*
    C++之后的版本
    Eigen::Matrix<double, 2, 5> mat{ {0, 1, 2, 3, 4}, {5, 6, 7, 8, 9} };
    */
    Eigen::Matrix3d mat;        mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    Eigen::RowVector3i rvec;    rvec << 1, 2, 3;
    Eigen::Array33d arr;        arr << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "Matrix\n" << mat  << endl;
    cout << "rvec\n"   << rvec << endl;
    cout << "arr\n"    << arr  << endl; 

    // 矩阵/数组的高级初始化
    // 1.逗号的使用
    Eigen::RowVector3i rv1, rv2;
    Eigen::Matrix<int, 1, 6> mat1;
    Eigen::Matrix<int, 2, 3> mat2;
    rv1 << 1, 2, 3;     cout << "rv1 = " << rv1 << endl;
    rv2 << 4, 5, 6;     cout << "rv2 = " << rv2 << endl;
    mat1 << rv1, rv2;   cout << "mat1 = " << mat1 << endl;
    mat2 << rv1, rv2;   cout << "mat2 = \n" << mat2 << endl;
    
    Eigen::Matrix2i mat3;
    Eigen::Matrix4i mat4;
    mat3 << 1, 2, 3, 4;
    mat4 << mat3, mat3 * 2, mat3 * 3, mat3 * 4;
    cout << "mat3 = \n" << mat3 << endl;
    cout << "mat4 = \n" << mat4 << endl;

   // 2.特殊矩阵的初始化
    //对于矩阵大小确定的，括号中可省略
 	 //对于动态大小矩阵，括号中要规定矩阵尺寸
    Eigen::Matrix3i A = Eigen::Matrix3i::Identity();        //单位矩阵  
    Eigen::RowVectorXd B = Eigen::RowVectorXd::Zero(3);     //零矩阵
    Eigen::ArrayXXd C = Eigen::ArrayXXd::Random(3, 3);      //随机数矩阵
    Eigen::Vector3i D = Eigen::Vector3i::Ones();            //元素全为1的矩阵
    cout << "A\n" << A << endl;
    cout << "B\n" << B << endl;
    cout << "C\n" << C << endl;
    cout << "D\n" << D << endl;

    // Constant函数 : 构建一个所有元素均相同的常数矩阵
    //对于矩阵大小确定的，括号中的是填充的数字
    Eigen::Matrix3i E = Eigen::Matrix3i::Constant(5);       
    //对于矩阵大小不确定的，括号中前面一位或两位定义矩阵尺寸，最后一位定义元素
    Eigen::RowVectorXd F = Eigen::RowVectorXd::Constant(3, 5);
    Eigen::ArrayXXd G = Eigen::ArrayXXd::Constant(2, 3, 5);
    cout << "E\n" << E << endl;
    cout << "F\n" << F << endl;
    cout << "G\n" << G << endl;

    // LinSpaced函数 : 构建一个线性间隔向量
    //1.只能用于向量、一维数组
 	//2.需要所分区间的上下限
    Eigen::RowVector4d rv_link = Eigen::RowVector4d::LinSpaced(0, 6);
    Eigen::ArrayXd arr_link = Eigen::ArrayXd::LinSpaced(3, 4, 8);
    cout << "rv_link = \n" << rv_link << endl;
    cout << "arr_link = \n" << arr_link << endl;

   // 3.临时对象的使用
   Eigen::Vector3d vec_;    vec_ << 1, 2, 3;
   Eigen::Matrix3d mat_ = Eigen::Matrix3d::Identity();
   Eigen::Matrix<double, 3, 4> MAT;    MAT << vec_, mat_;
   cout << "Vector + Matrix way1:\n" << MAT << endl;

   Eigen::Matrix<double, 3, 4> MAT_;
   MAT_ << (Eigen::Vector3d() << 1, 2, 3).finished(), Eigen::Matrix3d::Identity();
   cout << "Vector + Matrix way2:\n" << MAT_ << endl;



    return 0;
}