#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread("../p1.png");
    Mat dst1, dst2, dst_med, dst_bil;
    namedWindow("INPUT", WINDOW_FREERATIO);
    namedWindow("OUTPUT1", WINDOW_NORMAL);
    namedWindow("OUTPUT2", WINDOW_NORMAL);

    if(src.empty())
    {
        cout << "could not load the picture" << endl;
        return -1;
    }
    imshow("INPUT", src);
    waitKey(0);

    blur(src, dst1, Size(7, 7), Point(-1, -1));
    imshow("OUTPUT1", dst1);
    GaussianBlur(src, dst2, Size(7, 7), 11, 11);
    imshow("OUTPUT2", dst2);
    waitKey(0);
    
    blur(src, dst1, Size(30, 1), Point(-1, -1));
    imshow("OUTPUT1", dst1);
    waitKey(0);
    blur(src, dst1, Size(1, 30), Point(-1, -1));
    imshow("OUTPUT1", dst1);
    waitKey(0);
    destroyAllWindows();

    Mat src_polluted;
    src.copyTo(src_polluted);
    namedWindow("POLLUTE", WINDOW_FREERATIO);
    RNG rng(12345);
    Point p;
    for(int i=0; i<20; i++)
    {
        p.x = rng.uniform(0, src.cols);  p.y = rng.uniform(0, src.rows);
        if(i % 2 == 0)
            circle(src_polluted, p, 2, Scalar(0,0,0), -1, 8);
        else
            circle(src_polluted, p, 2, Scalar(255,255,255), -1, 8);
    }
    imshow("POLLUTE" ,src_polluted);
    waitKey(0);

    //median filtering
    medianBlur(src_polluted, dst_med, 7);
    namedWindow("MEDIAN", WINDOW_FREERATIO);
    imshow("MEDIAN", dst_med);

    //bilateral filter
    bilateralFilter(src_polluted, dst_bil, 15, 150, 3);
    namedWindow("BILATERAL", WINDOW_FREERATIO);
    imshow("BILATERAL", dst_bil);
    waitKey(0);
    destroyAllWindows();

    Mat rst;
    bilateralFilter(src, rst, 15, 100, 5);
    Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(rst, rst, -1, kernel, Point(-1, -1), 0);
    namedWindow("RESULT", WINDOW_FREERATIO);
    imshow("RESULT", rst);
    waitKey(0);
    destroyAllWindows();

    return 0;
}