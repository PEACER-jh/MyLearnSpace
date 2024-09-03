#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap;
    namedWindow("Iput", WINDOW_FREERATIO);
    namedWindow("Oput", WINDOW_FREERATIO);
    cap.open(0);

    if(!cap.isOpened())
    {
        cout << "Cannot open the web cam" << endl;
        return -1;
    }

    Mat frame;
double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
double fx = 458.654,     fy = 457.296,    cx = 367.215,    cy = 248.375;
    while(1)
    {
        cap >> frame;
        if(frame.empty())
        {
            cout << "Cannot get the camera frame" << endl;
            return -1;
        }
        imshow("Iput", frame);
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        Mat dst = Mat(frame.rows, frame.cols, CV_8UC1);
        int rows = frame.rows, cols = frame.cols;

        for(int v = 0; v < rows; v++)
            for(int u = 0; u < cols; u++)
        {   
double x = (u - cx) / fx , y = (v - cy) / fy;
double r = sqrt(x * x + y * y);
double x_d = x * (1 + k1*r*r + k2*r*r*r*r) + 2*p1*x*y + p2*(r*r + 2*x*x);
double y_d = y * (1 + k1*r*r + k2*r*r*r*r) + p1*(r*r + 2*y*y) + 2*p2*x*y;
double u_d = fx * x_d + cx;
double v_d = fy * y_d + cy;

        if(u_d >= 0 && v_d >= 0 && u_d < cols && v_d < rows)
            dst.at<uchar>(v, u) = frame.at<uchar>((int)v_d, (int)u_d);
        else
            dst.at<uchar>(v, u) = 0;
        }

        imshow("Oput", dst);

        if(waitKey(30) == 27)
            break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}