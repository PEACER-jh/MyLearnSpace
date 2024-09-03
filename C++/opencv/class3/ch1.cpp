#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int threshold_value = 127;
int threshold_max = 255;
int type_value = 0;
int type_max = 4;
Mat src, gray, dst;
const char* output_title = "OUTPUT";

void Threshold_Demo(int, void*);

int main(int argc, char **argv)
{
    src = imread("../p1.jpg");
    namedWindow("INPUT", WINDOW_FREERATIO);
    if(src.empty())
    {
        cout << "could not load the picture" << endl;
        return -1;
    }
    imshow("INPUT", src);

    printf("type = %d : THRESH_BINARY\n", THRESH_BINARY);             // 0
    printf("type = %d : THRESH_BINARY_INV\n", THRESH_BINARY_INV);     // 1
    printf("type = %d : THRESH_TRUNC\n", THRESH_TRUNC);               // 2
    printf("type = %d : THRESH_TOZERO\n", THRESH_TOZERO);             // 3
    printf("type = %d : THRESH_TOZERO_INV\n", THRESH_TOZERO_INV);     // 4

    namedWindow(output_title, WINDOW_FREERATIO);
    createTrackbar("Threshold Value", output_title, &threshold_value, threshold_max, Threshold_Demo);
    createTrackbar("Threshold Type", output_title, &type_value, type_max, Threshold_Demo);
    Threshold_Demo(0, 0);

    waitKey(0);
    destroyAllWindows();

    // auto threshold
    Mat at1, at2;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    threshold(gray, at1, 0, 255, THRESH_OTSU | THRESH_BINARY);
    namedWindow("AUTO1", WINDOW_FREERATIO);
    imshow("AUTO1", at1);

    threshold(gray, at2, 0, 255, THRESH_TRIANGLE | THRESH_BINARY);
    namedWindow("AUTO2", WINDOW_FREERATIO);
    imshow("AUTO2", at2);

    waitKey(0);
    destroyAllWindows();
    return 0;
}

void Threshold_Demo(int, void*)
{
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, dst, threshold_value, threshold_max, type_value);
    imshow(output_title, dst);
}