#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void drawLine(Mat src)
{
    Point p1 = Point(20, 30);
    Point p2;  p2.x = 300;  p2.y = 200;
    Scalar color = Scalar(0, 127, 255);
    line(src, p1, p2, color, 5, LINE_8);
}
void drawRectangle(Mat src)
{
    Rect rect = Rect(200, 100, 300, 300);
    Scalar color = Scalar(255, 127, 0);
    rectangle(src, rect, color, 2, LINE_AA);
}
void drawEllipse(Mat src)
{
    Point center = Point(src.cols/2, src.rows/2);
    Size axes = Size(src.cols/4, src.rows/2);
    Scalar color = Scalar(255, 0, 0);
    ellipse(src, center, axes, 90, 45, 270, color, 3, LINE_8);
}
void drawCircle(Mat src)
{
    Point center = Point(src.cols/2, src.rows/2);
    Scalar color = Scalar(0, 255, 0);
    circle(src, center, 200, color, -1, LINE_AA);
}
void drawPolygon(Mat src)
{
    Point pts[1][5];
    pts[0][0] = Point(100, 100);
    pts[0][1] = Point(100, 200);
    pts[0][2] = Point(200, 200);
    pts[0][3] = Point(200, 100);
    pts[0][4] = Point(100, 100);
    const Point *p_pts[] = { pts[0] };
    int n_pts[] = { 5 };
    Scalar color = Scalar(0, 0, 255);
    fillPoly(src, p_pts, n_pts, 1, color, LINE_8);
}

void RandomLine(Mat src);

int main(int argc, char **argv)
{
    Mat src = imread("../p1.png");
    namedWindow("INPUT", WINDOW_FREERATIO);
    namedWindow("OUTPUT", WINDOW_FREERATIO);
    if(src.empty() || !src.data)
    {
        cout << "could not load the picture" << endl;
        return -1;
    }
    imshow("INPUT", src);
    waitKey(0);
    Scalar text_color(0, 0, 0);

    drawLine(src);
    putText(src, "hello line", Point(20, 30), FONT_HERSHEY_COMPLEX, 1.0, text_color, 1, 8);
    imshow("OUTPUT", src);
    waitKey(0);
    
    drawRectangle(src);
    putText(src, "hello rectangle", Point(200, 100), FONT_HERSHEY_DUPLEX, 1.5, text_color, 1, 8);
    imshow("OUTPUT", src);
    waitKey(0);
    
    drawEllipse(src);
    putText(src, "hello ellipse", Point(src.cols/2+200, src.rows/2+200), FONT_HERSHEY_PLAIN, 2.0, text_color, 1, 8);
    imshow("OUTPUT", src);
    waitKey(0);
    
    drawCircle(src);
    putText(src, "hello circle", Point(src.cols/2+200, src.rows/2+250), FONT_HERSHEY_SIMPLEX, 2.5, text_color, 1, 8);
    imshow("OUTPUT", src);
    waitKey(0);
    
    drawPolygon(src);
    putText(src, "hello polygon", Point(200, 200), FONT_HERSHEY_TRIPLEX, 3.0, text_color, 1, 8);
    imshow("OUTPUT", src);
    waitKey(0);

    RandomLine(src);

    destroyAllWindows();
    return 0;
}

void RandomLine(Mat src)
{
    Mat dst = Mat::zeros(src.size(), src.type());
    namedWindow("RANDOM", WINDOW_AUTOSIZE);
    RNG rng(12345);
    Point p1, p2;
    for(int i=0; i<1000; i++)
    {
    p1.x = rng.uniform(0, src.cols);  p2.x = rng.uniform(0, src.cols);
    p1.y = rng.uniform(0, src.rows);  p2.y = rng.uniform(0, src.rows);
    Scalar color(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255));
    
    if(waitKey(50) > 0)
        break;
    
    line(dst, p1, p2, color, 1, LINE_8);
    imshow("RANDOM", dst);
    }
}