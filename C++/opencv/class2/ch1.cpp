#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread("../p1.png");
    Mat src_gray, src_bgr, src_32f;
    namedWindow("INPUT", WINDOW_FREERATIO);
    namedWindow("OUTPUT", WINDOW_FREERATIO);
    namedWindow("REVERSE1", WINDOW_FREERATIO);
    namedWindow("REVERSE2_1", WINDOW_FREERATIO);
    namedWindow("REVERSE2_2", WINDOW_FREERATIO);
    namedWindow("DEPTH", WINDOW_FREERATIO);
    namedWindow("GRAY", WINDOW_FREERATIO);

    if(src.empty() || !src.data)
    {
        cout << "could not load the picture" << endl;
        return -1;
    }
    imshow("INPUT", src);

    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    imshow("OUTPUT", src_gray);

    double time, delta;
    const int height = src.rows;
    const int width = src.cols;

    time = getTickCount();
    for(int row=0; row<height; row++)
        for(int col=0; col<width; col++)
    {
        int gray = src_gray.at<uchar>(row, col);
        src_gray.at<uchar>(row, col) = 255 - gray;
    }
    delta = (getTickCount() - time) / getTickFrequency();
    cout << "reverse1: " << delta << endl;
    imshow("REVERSE1", src_gray);

    src_bgr.create(src.size(), src.type());
    const int channel = src.channels();
    time = getTickCount();
    for(int row=0; row<height; row++)
        for(int col=0; col<width; col++)
    {
        if(channel == 1)
        {
            int gray = src_gray.at<uchar>(row, col);
            src_gray.at<uchar>(row, col) = 255 - gray;
        }
        else if(channel == 3)
        {
            int b = src.at<Vec3b>(row, col)[0];
            int g = src.at<Vec3b>(row, col)[1];
            int r = src.at<Vec3b>(row, col)[2];
            src_bgr.at<Vec3b>(row, col)[0] = 255 - b;
            src_bgr.at<Vec3b>(row, col)[1] = 255 - g;
            src_bgr.at<Vec3b>(row, col)[2] = 255 - r;

            // src_gray.at<uchar>(row, col) = max(r, max(g, b));
            src_gray.at<uchar>(row, col) = (r + g + b) / 3.0;
        }
    }
    delta = (getTickCount() - time) / getTickFrequency();
    cout << "reverse2_1: " << delta << endl;
    imshow("REVERSE2_1", src_bgr);
    imshow("GRAY", src_gray);

    time = getTickCount();
    bitwise_not(src, src_bgr);
    delta = (getTickCount() - time) / getTickFrequency();
    cout << "reverse2_2: " << delta << endl;
    imshow("REVERSE2_2", src_bgr);

    src.copyTo(src_32f);
    cout << "converTo before: " << src_32f.size() << " " << src_32f.type() << endl;
    src.convertTo(src_32f, CV_32FC3, 1/255.0);
    cout << "converTo after: " << src_32f.size() << " " << src_32f.type() << endl;
    imshow("DEPTH", src_32f);
    
    waitKey(0);
    destroyAllWindows();
    return 0;
}