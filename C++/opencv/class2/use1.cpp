#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat drawline(Mat zero);
Mat drawletter(Mat zero);

int main(int argc, char **argv)
{
    Mat zero = Mat::zeros(1000, 1000, CV_8UC3);
    // src = imread("../use.jpg");
    // namedWindow("INPUT", WINDOW_FREERATIO);
    // if(src.empty())
    // {
    //     cout << "could not load the picture" << endl;
    //     return -1;
    // }
    // imshow("INPUT", src);
    Mat src = drawline(zero);

    Mat gray;
    namedWindow("GRAY", WINDOW_FREERATIO);
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imshow("GRAY", gray);

    Mat bin;
    namedWindow("BIN", WINDOW_FREERATIO);
    adaptiveThreshold(gray, bin, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    imshow("BIN", bin);

    Mat dst;
    Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols/16, 1), Point(-1, -1));
    Mat vline = getStructuringElement(MORPH_RECT, Size(1, src.rows/16), Point(-1, -1));
    
    // erode(bin, dst, hline);
    // dilate(dst, dst, hline);
    morphologyEx(bin, dst, MORPH_OPEN, hline);
    blur(dst, dst, Size(3, 3), Point(-1, -1));
    namedWindow("HLINE", WINDOW_FREERATIO);
    imshow("HLINE", dst);

    // erode(bin, dst, vline);
    // dilate(dst, dst, vline);
    morphologyEx(bin, dst, MORPH_OPEN, vline);
    blur(dst, dst, Size(3, 3), Point(-1, -1));
    namedWindow("VLINE", WINDOW_FREERATIO);
    imshow("VLINE", dst);

    waitKey(0);
    destroyAllWindows();

    zero = Mat::zeros(1000, 1000, CV_8UC3);
    src = drawletter(zero);
    cvtColor(src, gray, COLOR_BGR2GRAY);
    adaptiveThreshold(gray, bin, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    bin.copyTo(dst);
    erode(dst, dst, kernel);
    dilate(dst, dst, kernel);
    // morphologyEx(dst, dst, MORPH_RECT, kernel);
    bitwise_not(dst, dst);
    namedWindow("KERNEL", WINDOW_FREERATIO);
    imshow("KERNEL", dst);


    waitKey(0);
    destroyAllWindows();
    return 0;
}

Mat drawline(Mat zero)
{
    namedWindow("RANDOM", WINDOW_FREERATIO);
    RNG rng(12345);
    Point ph_1, ph_2, pv_1, pv_2;
    for(int i=0; i<4; i++)
    {
        Scalar color(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255));
        int thick = rng.uniform(3, 8);
        
        ph_1.x = rng.uniform(0, zero.cols); ph_1.y = rng.uniform(0, zero.rows);
        ph_2.x = rng.uniform(0, zero.cols); ph_2.y = ph_1.y;
        line(zero, ph_1, ph_2, color, thick, LINE_8);
        
        pv_1.x = rng.uniform(0, zero.cols); pv_1.y = rng.uniform(0, zero.rows);
        pv_2.x = pv_1.x; pv_2.y = rng.uniform(0, zero.rows);
        line(zero, pv_1, pv_2, color, thick, LINE_8);

    if(waitKey(50) > 0)
        break;
    imshow("RANDOM", zero);
    } 
    return zero;
}
Mat drawletter(Mat zero)
{
    putText(zero, "A B C D", Point(zero.cols/5, zero.rows/2.0), FONT_HERSHEY_SIMPLEX, 5, Scalar(0, 0, 255), 30, 8);
    namedWindow("RANDOM", WINDOW_FREERATIO);
    RNG rng(12345);
    Point p1, p2;
    Point c1, c2;
    for(int i=0; i<5; i++)
    {
        p1.x = rng.uniform(100, 900);  p2.x = rng.uniform(100, 900);
        p1.y = rng.uniform(100, 900);  p2.y = rng.uniform(100, 900);
        c1.x = rng.uniform(100, 900);  c2.x = rng.uniform(100, 900);
        c1.y = rng.uniform(100, 900);  c2.y = rng.uniform(100, 900);
        Scalar color(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255));
    
    if(waitKey(50) > 0)
        break;
    
        line(zero, p1, p2, color, 4, LINE_8);
        circle(zero, c1, 2, color, -1, LINE_AA);
        circle(zero, c2, 3, color, -1, LINE_AA);
        imshow("RANDOM", zero);
    }
    return zero;
}
