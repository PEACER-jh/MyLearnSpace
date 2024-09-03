#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Sobel
int main(int argc, char **argv)
{
    Mat src = imread("../p1.jpg");
    namedWindow("INPUT", WINDOW_FREERATIO);
    if(src.empty())
    {
        cout << "could not load the picture" << endl;
        return -1;
    }
    imshow("INPUT", src);

    Mat dst;
    GaussianBlur(src, dst, Size(3, 3), 0, 0);
    cvtColor(dst, dst, COLOR_BGR2GRAY);

    Mat xgrad, ygrad;
    namedWindow("X_Sobel", WINDOW_FREERATIO);
    namedWindow("Y_Sobel", WINDOW_FREERATIO);
    Sobel(dst, xgrad, CV_16S, 1, 0, 3);
    Sobel(dst, ygrad, CV_16S, 0, 1, 3);
    convertScaleAbs(xgrad, xgrad);
    convertScaleAbs(ygrad, ygrad);
    imshow("X_Sobel", xgrad);
    imshow("Y_Sobel", ygrad);

    Mat xgrad_, ygrad_;
    namedWindow("X_Scharr", WINDOW_FREERATIO);
    namedWindow("Y_Scharr", WINDOW_FREERATIO);
    Sobel(dst, xgrad_, CV_16S, 1, 0, 3);
    Sobel(dst, ygrad_, CV_16S, 0, 1, 3);
    convertScaleAbs(xgrad_, xgrad_);
    convertScaleAbs(ygrad_, ygrad_);
    imshow("X_Scharr", xgrad_);
    imshow("Y_Scharr", ygrad_);

    Mat xygrad;
    addWeighted(xgrad, 0.5, ygrad, 0.5, 0, xygrad);
    namedWindow("XY_Sobel", WINDOW_FREERATIO);
    imshow("XY_Sobel", xygrad);

    Mat xygrad_;
    addWeighted(xgrad_, 0.5, ygrad_, 0.5, 0, xygrad_);
    namedWindow("XY_Scharr", WINDOW_FREERATIO);
    imshow("XY_Scharr", xygrad_);

    Mat xygrad_s = Mat(xgrad.size(), xgrad.type());
    namedWindow("XY_s", WINDOW_FREERATIO);
    int height = ygrad.rows;
    int width = xgrad.cols;
    for(int row = 0; row < height; row++)
        for(int col = 0; col < width; col++)
    {
        int xg = xgrad.at<uchar>(row, col);
        int yg = ygrad.at<uchar>(row, col);
        int xy = xg + yg;
        xygrad_s.at<uchar>(row, col) = static_cast<uchar>(xy);
    }
    imshow("XY_s", xygrad_s);



    waitKey(0);
    destroyAllWindows();
    return 0;
}