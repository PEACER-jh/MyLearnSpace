#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread("../use.jpg");
    namedWindow("INPUT", WINDOW_AUTOSIZE);
    if(src.empty())
    {
        cout << "could not load the picture" << endl;
        return -1;
    }
    imshow("INPUT", src);
    cout << "col of src: " << src.cols << " row of src: " << src.rows << endl;

    Mat dst_UP, dst_DOWN;
    namedWindow("OUT_UP", WINDOW_AUTOSIZE);
    namedWindow("OUT_DOWN", WINDOW_AUTOSIZE);

    // upsample / upsacle
    pyrUp(src, dst_UP, Size(src.cols*2, src.rows*2));
    imshow("OUT_UP", dst_UP);
    cout << "col of UP: " << dst_UP.cols << " row of UP: " << dst_UP.rows << endl;

    // downsample / downscale
    pyrDown(src, dst_DOWN, Size(src.cols/2, src.rows/2));
    imshow("OUT_DOWN", dst_DOWN);
    cout << "col of DOWN: " << dst_DOWN.cols << " row of DOWN: " << dst_DOWN.rows << endl;

    waitKey(0);
    destroyAllWindows();

    // normalized display
    Mat gray, g1, g2, DogImg;
    namedWindow("DOGIMAGE", WINDOW_FREERATIO);
    cvtColor(src, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, g1, Size(3, 3), 0, 0);
    GaussianBlur(g1, g2, Size(3, 3), 0, 0);
    subtract(g1, g2, DogImg, Mat());
    normalize(DogImg, DogImg, 255, 0, NORM_MINMAX);
    imshow("DOGIMAGE", DogImg);

    waitKey(0);
    destroyAllWindows();
    return 0;
}