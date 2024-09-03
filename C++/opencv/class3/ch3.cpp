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

    int top = (int)(0.05 * src.rows);
    int bottom = (int)(0.05 * src.rows);
    int left = (int)(0.05 * src.rows);
    int right = (int)(0.05 * src.rows);

    Mat dst;
    RNG rng(12345);
    namedWindow("OUTPUT", WINDOW_AUTOSIZE);
    int borderType = BORDER_DEFAULT;
    int c = 0;
    while (true)
    {
        c = waitKey(500);
        if((char)c == 27 || (char)c == 13)   //ESC
            break;
        else if((char)c == 'd')     borderType = BORDER_DEFAULT;
        else if((char)c == 'r')     borderType = BORDER_REPLICATE;
        else if((char)c == 'w')     borderType = BORDER_WRAP;      
        else if((char)c == 'c')     borderType = BORDER_CONSTANT;         

        Scalar color = Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255));
        copyMakeBorder(src, dst, top, bottom, left, right, borderType, color);
        imshow("OUTPUT", dst);
    }
    waitKey(0);
    destroyAllWindows();

    Mat dst_def, dst_rep, dst_wrp, dst_con;
    namedWindow("DEFAULT", WINDOW_FREERATIO);
    namedWindow("REPLICATE", WINDOW_FREERATIO);
    namedWindow("WRAP", WINDOW_FREERATIO);
    namedWindow("CONSTANT", WINDOW_FREERATIO);
    GaussianBlur(src, dst_def, Size(5,5), 0, 0, BORDER_DEFAULT);
    GaussianBlur(src, dst_rep, Size(5,5), 0, 0, BORDER_REPLICATE);
    GaussianBlur(src, dst_wrp, Size(5,5), 0, 0, BORDER_WRAP);
    GaussianBlur(src, dst_con, Size(5,5), 0, 0, BORDER_CONSTANT);
    imshow("DEFAULT", dst_def);
    imshow("REPLICATE", dst_rep);
    imshow("WRAP", dst_wrp);
    imshow("CONSTANT", dst_con);

    waitKey(0);
    destroyAllWindows();
    return 0;
}