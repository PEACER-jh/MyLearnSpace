#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense> 

using namespace std;
using namespace Eigen;

int main(int argc, char **argv)
{
    Eigen::Matrix3d mat1, mat2; //矩阵类 Matrix: 矩阵按矩阵整体进行操作
    Eigen::Array33d arr1, arr2; //数组类 Array : 数组类对矩阵内每一个元素进行操作
    mat1 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    mat2 = Eigen::Matrix3d::Identity(3, 3);
    cout << "Matrix:\n" << mat1 * mat2 << endl;
    arr1 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    arr2 = mat2.array();
    cout << "Array:\n" << arr1 * arr2 << endl;

    // 矩阵/数组的创建
    Eigen::Matrix<double, 3, 2> mat;        //Matrix<数据类型, 行数, 列数>
    mat = Eigen::Matrix<double, 3, 2>::Zero(3, 2);
    cout << "Matrix:\n" << mat << endl;
    Eigen::Array<double, 3, 2> arr;         //Array<数据类型, 行数, 列数>
    arr = Eigen::Array<double, 3, 2>::Zero(3, 2);
    cout << "Array:\n" << arr << endl;
    Eigen::Matrix<double, 3, Dynamic>   mat_dyn;
    Eigen::Array<double, Dynamic, 2>    arr_dyn;

    Eigen::Matrix3f mat_33f;        //3X3大小的方阵，数据类型为float
    Eigen::Matrix4i mat_44i;        //4X4大小的方阵，数据类型为int
    Eigen::Vector3f vec_31f;        //3X1大小的列向量
    Eigen::RowVector3i Rvec_13i;    //1X3大小的行向量
    vec_31f = Eigen::Vector3f::Ones();
    Rvec_13i = Eigen::RowVector3i::Ones();
    cout << "Vector:\n" << vec_31f << endl;
    cout << "RowVector:\n" <<Rvec_13i << endl;    

    Eigen::Array33f arr_33f;
    Eigen::Array44i arr_44i;
    Eigen::Array3d  arr_31d;     //创建数组列向量
    arr_31d = Eigen::Array3d::Ones();   
    cout << "ArrVector:\n" << arr_31d << endl;

    typedef Eigen::Matrix<double, 16, 16> RotationMatrix;
    RotationMatrix R = Eigen::Matrix<double, 16, 16>::Zero();
    cout << "typedef rotation matrix:\n" << R << endl;

    // cf : complex<float>
    // cd : complex<double>
    // Eigen::Matrix<complex<float>, 1, 3>  complex_float  = Eigen::Matrix<complex<float>, 1, 3>::Identity();
    // Eigen::Matrix<complex<double>, 1, 3> compelx_double = Eigen::Matrix<complex<double>, 1, 3>::Identity();
    Eigen::Matrix3cf complex_float  = Eigen::Matrix3cf::Identity();
    Eigen::Matrix3cd compelx_double = Eigen::Matrix3cd::Identity();
    cout << "cf matrix:\n" << complex_float << endl;
    cout << "cd matrix:\n" << compelx_double << endl;

    //  矩阵类和数组类可以相互转换
    cout << "Matrix to Array:\n" << mat.array() << endl;
    cout << "Array to Matrix:\n" << arr.matrix() << endl;

    return 0;
}