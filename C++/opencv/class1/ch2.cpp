#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread("../p1.jpg");
    Mat dst1 = Mat::zeros(src.size(), src.type());
    Mat dst2 = Mat::zeros(src.size(), src.type());
    if(src.empty() || !src.data)
    {
        cout << "could not load the picture" << endl;
        return -1;
    }

    namedWindow("INTPUT", WINDOW_NORMAL);
    namedWindow("OUTPUT1", WINDOW_NORMAL);
    namedWindow("OUTPUT2", WINDOW_NORMAL);

    double time, delta; 

    time = getTickCount();
    const int cols = (src.cols - 1) * src.channels();
    const int rows = src.rows;
    const int offsetx = src.channels();
    for(int row = 1; row < (rows-1); row++)
    {
        const uchar* previous = src.ptr<uchar>(row - 1);
        const uchar* current = src.ptr<uchar>(row);
        const uchar* next = src.ptr<uchar>(row + 1);
        uchar* output = dst1.ptr<uchar>(row);
        for(int col = offsetx; col < cols; col++)
        {
            output[col] = saturate_cast<uchar>(5*current[col] - 
                        (current[col-offsetx] + current[col+offsetx] + previous[col] + next[col]));
        }
    }
    delta = (getTickCount() - time) / getTickFrequency();
    cout << "1:" << delta << endl;

    time = getTickCount();
    Mat kernel = (Mat_<char>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(src, dst2, src.depth(), kernel);
    delta = (getTickCount() - time) / getTickFrequency();
    cout << "2:" << delta << endl;

    imshow("INTPUT", src);
    imshow("OUTPUT1", dst1);
    imshow("OUTPUT2", dst2);
    waitKey(0);
    destroyAllWindows();

    return 0;
}