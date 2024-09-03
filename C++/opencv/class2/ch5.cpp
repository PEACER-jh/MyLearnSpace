#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat src = imread("../bw.png");
Mat dst;
int element_size = 3;
int max_size = 21;
char name_in[] = "INPUT";
char name_out[] = "OUTPUT";
 
void CallBack_Dilate(int, void*);
void CallBack_Erode(int, void*);
void CallBack_Open(int, void*);
void CallBack_Close(int, void*);
void CallBack_Gradient(int, void*);
void CallBack_TopHat(int, void*);
void CallBack_BlackHat(int, void*);

int main(int argc, char **argv)
{
    if(src.empty())
    {
        cout << "could not load the picture" << endl;
        return -1;
    }
    namedWindow(name_in, WINDOW_FREERATIO);
    namedWindow(name_out, WINDOW_FREERATIO);
    imshow("INPUT", src);

    cout << "choose: " << endl << " 1:DILATE" << endl 
                               << " 2:ERODE" << endl
                               << " 3:OPEN" << endl         // erode -> dilate
                               << " 4:CLOSE" << endl        // dilate -> erode
                               << " 5.GRADIENT" << endl     // dilate - erode
                               << " 6.TOPHAT" << endl       // src - open = src - (erode -> dilate)
                               << " 7.BLACKHAT" << endl;    // close - src = (dilate -> erode) - src
    int choice;
    cin >> choice;
    switch(choice)
    {
        case 1:
            CallBack_Dilate(0, 0);
            createTrackbar("Element Size: ", name_out, &element_size, max_size, CallBack_Dilate);   

            break; 
        case 2:
            CallBack_Erode(0, 0);
            createTrackbar("Element Size: ", name_out, &element_size, max_size, CallBack_Erode);   
            break;
        case 3:
            CallBack_Open(0, 0);
            createTrackbar("Element Size: ", name_out, &element_size, max_size, CallBack_Open);   
            break;
        case 4:
        circle(src, Point(src.size().width/4.0, src.size().height/3.0), 20, Scalar(0,0,0), -1, LINE_AA);
            CallBack_Close(0, 0);
            createTrackbar("Element Size: ", name_out, &element_size, max_size, CallBack_Close);   
            break;
        case 5:
            CallBack_Gradient(0, 0);
            createTrackbar("Element Size: ", name_out, &element_size, max_size, CallBack_Gradient);   
            break;
        case 6:
            CallBack_TopHat(0, 0);
            createTrackbar("Element Size: ", name_out, &element_size, max_size, CallBack_TopHat);   
            break;
        case 7:
        circle(src, Point(src.size().width/4.0, src.size().height/3.0), 20, Scalar(0,0,0), -1, LINE_AA);
            CallBack_BlackHat(0, 0);
            createTrackbar("Element Size: ", name_out, &element_size, max_size, CallBack_BlackHat);   
            break;
        default:
            cout << "ERROR!";
            break;
    }
    
    waitKey(0);
    destroyAllWindows;
    return 0;
}

void CallBack_Dilate(int, void*)
{
    int s = element_size * 2 + 1;
    Mat se = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    dilate(src, dst, se, Point(-1, -1), 1);
    imshow("OUTPUT", dst);
}
void CallBack_Erode(int, void*)
{
    int s = element_size * 2 + 1;
    Mat se = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    erode(src, dst, se, Point(-1, -1), 1);
    imshow("OUTPUT", dst);
}

void CallBack_Open(int, void*)
{
    int s = element_size * 2 + 1;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    morphologyEx(src, dst, MORPH_OPEN, kernel);
    imshow("OUTPUT", dst);
}
void CallBack_Close(int, void*)
{
    int s = element_size * 2 + 1;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    morphologyEx(src, dst, MORPH_CLOSE, kernel);
    imshow("OUTPUT", dst);
}
void CallBack_Gradient(int, void*)
{
    int s = element_size * 2 + 1;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    morphologyEx(src, dst, MORPH_GRADIENT, kernel);
    imshow("OUTPUT", dst);
}
void CallBack_TopHat(int, void*)
{
    int s = element_size * 2 + 1;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    morphologyEx(src, dst, MORPH_TOPHAT, kernel);
    imshow("OUTPUT", dst);
}
void CallBack_BlackHat(int, void*)
{
    int s = element_size * 2 + 1;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    morphologyEx(src, dst, MORPH_BLACKHAT, kernel);
    imshow("OUTPUT", dst);
}