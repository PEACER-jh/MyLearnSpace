#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    cout << "HELLO OPENCV!" << endl;

    Mat src1 = imread("../p1.jpg", 1);       //IMREAD_UNCHANGED
    Mat src2 = imread("../p1.jpg", 0);       //IMREAD_GRAYSCALE
    Mat src3 = imread("../p1.jpg", -1);      //IMREAD_COLOR
    namedWindow("UNCHANGED", WINDOW_NORMAL);
    namedWindow("GRAYSCALE", WINDOW_NORMAL);
    namedWindow("COLOR", WINDOW_NORMAL);
    imshow("UNCHANGED", src1);
    imshow("GRAYSCALE", src2);
    imshow("COLOR", src3);
    waitKey(0);
    destroyAllWindows();

    Mat src1_change1, src1_change2;
    cvtColor(src1, src1_change1, COLOR_BGR2GRAY);
    cvtColor(src1, src1_change2, COLOR_BGR2HLS);
    namedWindow("cvtColor1", WINDOW_NORMAL);
    namedWindow("cvtColor2", WINDOW_NORMAL);
    imshow("cvtColor1", src1_change1);
    imshow("cvtColor2", src1_change2);
    waitKey(0);
    destroyAllWindows();

    // imwrite("../p1_gray.jpg", src1_change1);
    // imwrite("../p1_hls.png", src1_change2);


    return 0;
}