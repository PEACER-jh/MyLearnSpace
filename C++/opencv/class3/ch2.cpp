#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

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

    // Robert
    Mat robert_dst_x, robert_dst_y;
    Mat robert_kernel_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
    Mat robert_kernel_y = (Mat_<int>(2, 2) << 0, 1, -1, 0);
    filter2D(src, robert_dst_x, -1, robert_kernel_x, Point(-1,-1), 0.0);
    filter2D(src, robert_dst_y, -1, robert_kernel_y, Point(-1,-1), 0.0);
    namedWindow("ROBERT_X", WINDOW_FREERATIO);
    namedWindow("ROBERT_Y", WINDOW_FREERATIO);
    imshow("ROBERT_X", robert_dst_x);
    imshow("ROBERT_Y", robert_dst_y);
    imshow("ROBERT_ADD", robert_dst_x + robert_dst_y);
    waitKey(0);
    destroyAllWindows();

    // Sobel 
    Mat sobel_dst_x, sobel_dst_y;
    Mat sobel_kernel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    Mat sobel_kernel_y = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    filter2D(src, sobel_dst_x, -1, sobel_kernel_x, Point(-1,-1), 0.0);
    filter2D(src, sobel_dst_y, -1, sobel_kernel_y, Point(-1,-1), 0.0);
    namedWindow("SOBEL_X", WINDOW_FREERATIO);
    namedWindow("SOBEL_Y", WINDOW_FREERATIO);
    imshow("SOBEL_X", sobel_dst_x);
    imshow("SOBEL_Y", sobel_dst_y);
    imshow("SOBEL_ADD", sobel_dst_x + sobel_dst_y);
    waitKey(0);
    destroyAllWindows();

    // Laplace
    Mat laplace_dst;
    Mat laplace_kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
    filter2D(src, laplace_dst, -1, laplace_kernel, Point(-1,-1), 0.0);
    imshow("LAPLACE", laplace_dst);
    waitKey(0);
    destroyAllWindows();

    int c = 0;
    int index = 0;
    int ksize = 3;
    Mat dst;
    namedWindow("OUTPUT", WINDOW_AUTOSIZE);
    while(true)
    {
        c = waitKey(500);
        if((char)c == 27 || (char)c == 13)   //ESC
            break;

        ksize = 4 + (index % 5) * 2 +1;
        Mat kernel = Mat::ones(Size(ksize, ksize), CV_32F) / (float)(ksize * ksize);
        filter2D(src, dst, -1, kernel, Point(-1, -1), 0.0);
        index++;
        imshow("OUTPUT", dst);
    }

    return 0;
}