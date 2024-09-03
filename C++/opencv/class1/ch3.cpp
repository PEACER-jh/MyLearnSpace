#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread("../p1.jpg");
    namedWindow("OUTPUT", WINDOW_FREERATIO);
    if(src.empty() || !src.data)
    {
        cout << "could not load the picture" << endl;
        return -1;
    }

    Mat dst;
    
    dst = Mat(src.size(), src.type());
    dst = Scalar(127, 127, 127);
    imshow("OUTPUT", dst);
    waitKey(0);

    dst = src.clone();
    imshow("OUTPUT", dst);
    waitKey(0);
    src.copyTo(dst);
    imshow("OUTPUT", dst);
    waitKey(0);

    cvtColor(src, dst, COLOR_BGR2GRAY);
    cout << "channels of  input image: " << src.channels() << endl;
    cout << "channels of output image: " << dst.channels() << endl;
    cout << endl;

    int cols = dst.cols;
    int rows = dst.rows;
    printf("col: %d  row: %d\n", cols, rows);
    const uchar *FirstRow = dst.ptr<uchar>(0);
    cout << "first pixel value : " << (int)*FirstRow << endl;
    cout << endl;

    dst = Mat(3, 3, CV_8UC3, Scalar(0, 127, 255));
    cout << "way1 : dst = " << endl << dst << endl;
    cout << endl;
    imshow("OUTPUT", dst);
    waitKey(0);

    dst.create(dst.size(), dst.type());
    dst = Scalar(255, 127, 0);
    cout << "way2 : dst = " << endl << dst << endl;
    cout << endl;
    imshow("OUTPUT", dst);
    waitKey(0);

    dst = Mat::zeros(2, 2, CV_8UC1);
    cout << "way3 : dst(.zeros()) = " << endl << dst << endl;
    cout << endl;
    namedWindow("ZEROS", WINDOW_FREERATIO);
    imshow("ZEROS", dst);
    waitKey(0);

    dst = Mat::eye(2, 2, CV_8UC1);
    cout << "way3 : dst(.eye()) = " << endl << dst << endl;
    cout << endl;
    namedWindow("EYE", WINDOW_FREERATIO);
    imshow("EYE", dst);
    waitKey(0);


    destroyAllWindows();
    return 0;
}