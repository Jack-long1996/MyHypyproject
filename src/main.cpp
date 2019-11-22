#include <iostream>
#include <opencv2/opencv.hpp>
#include "../include/Hyperspectralimage.h"

using namespace std;
using namespace cv;
using namespace Himage;

Hyperspectralimage myHimage("../data/free1.bmp","../data/free1.bmp","../data/rgbimage0.png");

void on_mouse1(int event, int x, int y, int flags, void *ustc)
{
    myHimage.on_mouse1(event,x,y);
}
void on_mouse2(int event, int x, int y, int flags, void *ustc)
{
    myHimage.on_mouse2(event,x,y);
}
void on_mouse3(int event, int x, int y, int flags, void *ustc)
{
    myHimage.on_mouse3(event,x,y);
}
void on_mouse4(int event, int x, int y, int flags, void *ustc)
{
    myHimage.on_mouse4(event,x,y);
}
void on_mouse5(int event, int x, int y, int flags, void *ustc)
{
    myHimage.on_mouse5(event,x,y);
}
void on_mouse6(int event, int x, int y, int flags, void *ustc)
{
    myHimage.on_mouse6(event,x,y);
}
int main() {
    myHimage.createallimages();
    myHimage.rebuildallimage();
    cv::imshow("white_image_A", myHimage.white_image_A);
    cv::setMouseCallback("white_image_A", on_mouse1);
    cv::imshow("white_image_B", myHimage.white_image_B);
    cv::setMouseCallback("white_image_B", on_mouse2);
    cv::imshow("white_image_C", myHimage.white_image_C);
    cv::setMouseCallback("white_image_C", on_mouse3);
    cv::imshow("white_image_D", myHimage.white_image_D);
    cv::setMouseCallback("white_image_D", on_mouse4);
    cv::waitKey(0);
    myHimage.calibrationallimage();
    myHimage.saveallimages("../data/");

    myHimage.xmlwritefilename = "../data/vocabulary.xml";
    myHimage.xmlreadfilename = "../data/vocabulary.xml";
    myHimage.pattern_bmp = "../data/first_calibration_image_*.bmp";
    myHimage.StartImageregistration("../data/rgbimage0.png","../data/first_image_0.bmp");
    cv::imshow("待配准图", myHimage.src_win);
    cv::setMouseCallback("待配准图", on_mouse6);
    cv::imshow("基准图", myHimage.ref_win);
    cv::setMouseCallback("基准图", on_mouse5);
    cv::waitKey(0);
    myHimage.Image_registration();
    myHimage.Image_allregistration();

    return 0;
}