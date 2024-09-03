#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense> 
#include <execution>

using namespace std;
using namespace Eigen;

int main(int argc, char **argv)
{
    // 矩阵/数组的索引
	    //1.索引从0开始，不是从1开始
	    //2.索引时，括号中需要填写int型变量
	    //3.对于行向量和列向量，括号里可以只写一个数字

    Eigen::Matrix3d mat = Eigen::Matrix3d::Random();
    mat(0, 0) = 0;  mat(1, 1) = 1;  mat(2, 2) = 2;
    cout << "mat = \n" << mat << endl;
    Vector3d vec = Eigen::Vector3d::Zero();
    vec(0) = 0; vec(1) = 1; vec(2) = 2;
    cout << "vec = \n" << vec << endl;

    int n = 2;
    Eigen::MatrixXd mat_ = Eigen::MatrixXd::Zero(6*n, 6*n);
    for(int i = 0; i < n; i++)
    {
        mat_(6*i+0, 6*i+0) = 1;
        mat_(6*i+1, 6*i+1) = 1;
        mat_(6*i+2, 6*i+2) = 1;
        mat_(6*i+3, 6*i+3) = 2;
        mat_(6*i+4, 6*i+4) = 2;
        mat_(6*i+5, 6*i+5) = 2;
    }
    cout << "mat_\n" << mat_ << endl;

    // 块处理
    Eigen::MatrixXd mat_block = Eigen::MatrixXd::Random(5, 5);
    cout << "random mat_block = \n" << mat_block << endl;
    //1. matrix.block(i,j,p,q)
    cout << "block way1: \n" << mat_block.block(0, 0, 2, 3) << endl;
    //2. matrix.block<p,q>(i,j)
    cout << "block way2: \n" << mat_block.block<2, 3>(0, 0) << endl;
    Eigen::Matrix<double, 2, 3> block1 = mat_block.block(0, 0, 2, 3);
    Eigen::Matrix<double, 2, 3> block2 = mat_block.block<2, 3>(0, 0);
    if(block1 == block2)    cout << "TRUE" << endl;
    else                    cout << "False" << endl;
    //3. matrix.row(i)	列索引
    //   matrix.col(j)	行索引
    cout << "row = \n" << mat_block.row(1) << endl;
    cout << "col = \n" << mat_block.col(1) << endl;

    Eigen::RowVectorXd rvc_block = Eigen::RowVectorXd::Random(6);
    cout << "rvc = " << rvc_block << endl;
    //4. matrix.head(n)       从头索引n个值
    //   matrix.tail(n)	      从尾索引n个值
    //   matrix.segment(n, m) 从中间索引，n为起始位置，m为索引数量
    cout << "head = " << rvc_block.head(4) << endl;
    cout << "tail = " << rvc_block.tail(4) << endl; 
    cout << "segment = " << rvc_block.segment(1, 4) << endl;

    //5.其他
    cout << "top left = \n" << mat_block.topLeftCorner(2, 3) << endl;
    cout << "bottom left = \n" << mat_block.bottomLeftCorner(2, 3) << endl;
    cout << "top right = \n" << mat_block.topRightCorner(2, 3) << endl;
    cout << "bottom right = \n" << mat_block.bottomRightCorner(2, 3) << endl;
    cout << "top rows = " << mat_block.topRows(1) << endl;
    cout << "bottom rows = " << mat_block.bottomRows(1) << endl;
    cout << endl;

    // 切片 ???
    // Eigen::MatrixXd mat_slice = Eigen::MatrixXd::Random(5, 5);
    // cout << "random mat_slice = \n" << mat_slice << endl;
    
    // Eigen::Vector3i v_ = (Eigen::Vector3i() << 1, 3, 4).finished();
    // Eigen::Array3i  a_ = (Eigen::Array3i()  << 1, 3, 4).finished();
    // int          n_[3] = {1, 3, 4};
    // cout << mat_slice(v_, v_) << endl;
    // cout << mat_slice(a_, a_) << endl;
    // cout << mat_slice(n_, n_) << endl;

    // 构造等差数列
    //seq(firstIdx ,lastIdx)		(起始索引, 终止索引)
	//seq(firstIdx, lastIdx, incr)	(起始索引, 终止索引, 步长)
	//seqN(first, size)		        (起始索引, 尺寸)
	//seqN(first, size, incr)	    (起始索引, 尺寸, 步长)
    // Eigen::MatrixXd mat_slice = Eigen::MatrixXd::Zero(6, 6);
    // for(int i = 0; i < 6; i++)
    //     mat_slice.col(i) << i, i, i, i, i,i;
    // cout << "mat_slice = \n" << mat_slice << endl;
    // cout << "slice = \n" << mat_slice(seq(0, 4, 2), seqN(1, 3, 2)) << endl;

    
    return 0;
}