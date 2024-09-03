#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src1 = imread("../1.jpg");
    Mat src2 = imread("../2.jpg");
    Mat dst;
    namedWindow("INPUT1", WINDOW_FREERATIO);
    namedWindow("INPUT2", WINDOW_FREERATIO);
    namedWindow("OUTPUT_ADD", WINDOW_FREERATIO);
    namedWindow("OUTPUT_MUL", WINDOW_FREERATIO);
    namedWindow("OUTPUT", WINDOW_FREERATIO);

    if(src1.empty() || !src2.data)
    {
        cout << "could not load the picture" << endl;
        return -1;
    }
    if(src1.size() != src2.size() || src1.type() != src2.type())
    {
        cout << "size or type of picture not same" << endl;
        return -2;
    }
    imshow("INPUT1", src1);
    imshow("INPUT2", src2);
    
    add(src1, src2, dst, Mat());
    imshow("OUTPUT_ADD", dst);
    multiply(src1, src2, dst, 1.0);
    imshow("OUTPUT_MUL", dst);

    // g(x) = (1-a)*f0(x) + a*f1(x)
    double alpha =0.5;
    double beta = 1.0 - alpha;
    addWeighted(src1, alpha, src2, beta, 0, dst);
    imshow("OUTPUT", dst);

    waitKey(0);
    destroyAllWindows();

    Mat src = imread("../p1.png");
    namedWindow("INPUT", WINDOW_FREERATIO);
    namedWindow("OUTPUT1", WINDOW_FREERATIO);
    namedWindow("OUTPUT2", WINDOW_FREERATIO);
    if(src.empty())
    {
        cout << "could not load the picture" << endl;
        return -1;
    }
    imshow("INPUT", src);
    const int height = src.rows;
    const int width = src.cols;
    dst = Mat::zeros(src.size(), src.type());
    //g(i,j) = a*f(i,j) + b
    alpha = 1.5;
    beta = 30;
    double time, delta;
    time = getTickCount();
    for(int row=0; row<height; row++)
        for(int col=0; col<width; col++)
    {
        if(src.channels() == 3)
        {
            float b = src.at<Vec3b>(row, col)[0];
            float g = src.at<Vec3b>(row, col)[1];
            float r = src.at<Vec3b>(row, col)[2];
            dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b * alpha + beta);
            dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g * alpha + beta);
            dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r * alpha + beta);
        }
        else if(src.channels() == 1)
        {
            float v = src.at<uchar>(row, col);
            dst.at<uchar>(row, col) = saturate_cast<uchar>(v * alpha + beta);
        }
    }
    delta = (getTickCount() - time) / getTickFrequency();
    cout << "way1: " << delta << endl;
    imshow("OUTPUT1", dst);

    time = getTickCount();
    src.convertTo(dst, -1, alpha, beta);
    delta = (getTickCount() - time) / getTickFrequency();
    cout << "way1: " << delta << endl;
    imshow("OUTPUT2", dst);

    waitKey(0);
    destroyAllWindows();
    return 0;
}