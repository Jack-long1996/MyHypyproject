//
// Created by ubuntu on 11/1/19.
//
#include <iostream>
#include <string.h>
#include <opencv2/opencv.hpp>
#include "../include/Hyperspectralimage.h"

using namespace std;
using namespace cv;
using namespace Himage;

namespace Himage{
    Hyperspectralimage::Hyperspectralimage(string opfilename,string owfilename,string rgbfilename){
		rowNumber = 217;  //行数
		colNumber = 409;  //列数
        passageNumber = 5;
        Image = cv::imread(opfilename,IMREAD_GRAYSCALE);
		WhiteIamge = cv::imread(owfilename,IMREAD_GRAYSCALE);
        RGBImage = cv::imread(rgbfilename);
    }
    Hyperspectralimage::~Hyperspectralimage(){

    }
    void Hyperspectralimage::StartImageregistration(string reffilename,string srcfilename)
    {
        //读入标定图像
        Mat refimg = imread(reffilename);    //基准图
        Mat srcimg = imread(srcfilename);    //待配准图
        cvtColor(refimg,ref_win,COLOR_BGR2GRAY); //基准图
        cvtColor(srcimg,src_win,COLOR_BGR2GRAY); //基准图
    }
    void Hyperspectralimage::Image_allregistration()
    {
        //读入变换矩阵
        FileStorage fsread(xmlreadfilename, FileStorage::READ);
        Mat mat_vocabulary;
        fsread["vocabulary"] >> mat_vocabulary;
        //对所有光谱图像进行校准
        Mat imageTransform;

        vector<cv::String> image_files;
        glob(pattern_bmp, image_files);
        if (image_files.size() == 0) {
            std::cout << "No image files[bmp]" << std::endl;
        }
        std::cout << image_files.size() << std::endl;
        for (unsigned int frame = 0; frame < image_files.size(); ++frame)
        {
            Mat image = imread(image_files[frame]);
            warpPerspective(image, imageTransform, mat_vocabulary, Size(RGBImage.cols, RGBImage.rows), INTER_LINEAR);
            cv::imwrite(image_files[frame], imageTransform);
        }
        cv::imshow("Mulispectul result Image", imageTransform);
        cv::waitKey();
    }
    void Hyperspectralimage::Image_registration()
    {
        //求变换矩阵
        Mat homo = findHomography(imagePoints2, imagePoints1, RANSAC);
        //Mat homo = findHomography(src_corners, ref_corners, RANSAC);
        //0 - a regular method using all the points, i.e., the least squares method
        //RANSAC - RANSAC-based robust method
        //LMEDS - Least-Median robust method
        //RHO - PROSAC-based robust method
        cout<<"变换矩阵计算"<<endl;

        //存储变换矩阵
        FileStorage fswrite(xmlwritefilename, FileStorage::WRITE);
        fswrite<<"vocabulary"<<homo;
        fswrite.release();

        std::cout<<"变换成功"<<std::endl;
    }

    void Hyperspectralimage::on_mouse5(int event, int x, int y)
    {
        if (event == EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处打点
        {
            Point  p = Point(x, y);
            circle(ref_win, p, 1, 255, -1);
            cv::imshow("基准图", ref_win);
            imagePoints1.push_back(p);   //将选中的点存起来
            cout << "基准图: " << p << endl;
            pcount++;
            cout << "ponit num:" << pcount << endl;
        }
    }
    void Hyperspectralimage::on_mouse6(int event, int x, int y)
    {
        if (event == EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处打点
        {
            Point  p = Point(x, y);
            circle(src_win, p, 1, 255, -1);
            imshow("待配准图", src_win);
            imagePoints2.push_back(p);   //将选中的点存起来
            cout << "待配准图: " << p << endl;
        }
    }
    void Hyperspectralimage::calibrationallimage()
    {
        first_0_sum[0] = 0.99;first_0_sum[1] = 0.5;first_0_sum[2] = 0.25;first_0_sum[3] = 0.1;
        first_1_sum[0] = 0.99;first_1_sum[1] = 0.5;first_1_sum[2] = 0.25;first_1_sum[3] = 0.1;
        first_2_sum[0] = 0.99;first_2_sum[1] = 0.5;first_2_sum[2] = 0.25;first_2_sum[3] = 0.1;
        first_3_sum[0] = 0.99;first_3_sum[1] = 0.5;first_3_sum[2] = 0.25;first_3_sum[3] = 0.1;
        first_4_sum[0] = 0.99;first_4_sum[1] = 0.5;first_4_sum[2] = 0.25;first_4_sum[3] = 0.1;
        first_5_sum[0] = 0.99;first_5_sum[1] = 0.5;first_5_sum[2] = 0.25;first_5_sum[3] = 0.1;
        first_6_sum[0] = 0.99;first_6_sum[1] = 0.5;first_6_sum[2] = 0.25;first_6_sum[3] = 0.1;
        first_7_sum[0] = 0.99;first_7_sum[1] = 0.5;first_7_sum[2] = 0.25;first_7_sum[3] = 0.1;
        first_8_sum[0] = 0.99;first_8_sum[1] = 0.5;first_8_sum[2] = 0.25;first_8_sum[3] = 0.1;
        first_9_sum[0] = 0.99;first_9_sum[1] = 0.5;first_9_sum[2] = 0.25;first_9_sum[3] = 0.1;
        first_10_sum[0] = 0.99;first_10_sum[1] = 0.5;first_10_sum[2] = 0.25;first_10_sum[3] = 0.1;
        first_11_sum[0] = 0.99;first_11_sum[1] = 0.5;first_11_sum[2] = 0.25;first_11_sum[3] = 0.1;
        first_12_sum[0] = 0.99;first_12_sum[1] = 0.5;first_12_sum[2] = 0.25;first_12_sum[3] = 0.1;
        first_13_sum[0] = 0.99;first_13_sum[1] = 0.5;first_13_sum[2] = 0.25;first_13_sum[3] = 0.1;
        first_14_sum[0] = 0.99;first_14_sum[1] = 0.5;first_14_sum[2] = 0.25;first_14_sum[3] = 0.1;
        first_15_sum[0] = 0.99;first_15_sum[1] = 0.5;first_15_sum[2] = 0.25;first_15_sum[3] = 0.1;
        first_16_sum[0] = 0.99;first_16_sum[1] = 0.5;first_16_sum[2] = 0.25;first_16_sum[3] = 0.1;
        first_17_sum[0] = 0.99;first_17_sum[1] = 0.5;first_17_sum[2] = 0.25;first_17_sum[3] = 0.1;
        first_18_sum[0] = 0.99;first_18_sum[1] = 0.5;first_18_sum[2] = 0.25;first_18_sum[3] = 0.1;
        first_19_sum[0] = 0.99;first_19_sum[1] = 0.5;first_19_sum[2] = 0.25;first_19_sum[3] = 0.1;
        first_20_sum[0] = 0.99;first_20_sum[1] = 0.5;first_20_sum[2] = 0.25;first_20_sum[3] = 0.1;
        first_21_sum[0] = 0.99;first_21_sum[1] = 0.5;first_21_sum[2] = 0.25;first_21_sum[3] = 0.1;
        first_22_sum[0] = 0.99;first_22_sum[1] = 0.5;first_22_sum[2] = 0.25;first_22_sum[3] = 0.1;
        first_23_sum[0] = 0.99;first_23_sum[1] = 0.5;first_23_sum[2] = 0.25;first_23_sum[3] = 0.1;
        first_24_sum[0] = 0.99;first_24_sum[1] = 0.5;first_24_sum[2] = 0.25;first_24_sum[3] = 0.1;

        OutFile.open("../data/CalibrationTest.txt");
        float aa,bb,rr;
        //0
        first_image_0_sum[0] =  first_image_0_sum[0]/count_A;first_image_0_sum[1] =  first_image_0_sum[1]/count_B;
        first_image_0_sum[2] =  first_image_0_sum[2]/count_C;first_image_0_sum[3] =  first_image_0_sum[3]/count_D;
        LineFitLeastSquares(first_image_0_sum,first_0_sum,4,aa,bb,rr);
        calibration_image(original_p_img_877,calibration_img_877,aa,bb);
        OutFile <<rr<<",";
        //1
        first_image_1_sum[0] =  first_image_1_sum[0]/count_A;first_image_1_sum[1] =  first_image_1_sum[1]/count_B;
        first_image_1_sum[2] =  first_image_1_sum[2]/count_C;first_image_1_sum[3] =  first_image_1_sum[3]/count_D;
        LineFitLeastSquares(first_image_1_sum,first_1_sum,4,aa,bb,rr);
        calibration_image(original_p_img_886,calibration_img_886,aa,bb);
        OutFile <<rr<<",";
        //2
        first_image_2_sum[0] =  first_image_2_sum[0]/count_A;first_image_2_sum[1] =  first_image_2_sum[1]/count_B;
        first_image_2_sum[2] =  first_image_2_sum[2]/count_C;first_image_2_sum[3] =  first_image_2_sum[3]/count_D;
        LineFitLeastSquares(first_image_2_sum,first_2_sum,4,aa,bb,rr);
        calibration_image(original_p_img_869,calibration_img_869,aa,bb);
        OutFile <<rr<<",";
        //3
        first_image_3_sum[0] =  first_image_3_sum[0]/count_A;first_image_3_sum[1] =  first_image_3_sum[1]/count_B;
        first_image_3_sum[2] =  first_image_3_sum[2]/count_C;first_image_3_sum[3] =  first_image_3_sum[3]/count_D;
        LineFitLeastSquares(first_image_3_sum,first_3_sum,4,aa,bb,rr);
        calibration_image(original_p_img_858,calibration_img_858,aa,bb);
        OutFile <<rr<<",";
        //4
        first_image_4_sum[0] =  first_image_4_sum[0]/count_A;first_image_4_sum[1] =  first_image_4_sum[1]/count_B;
        first_image_4_sum[2] =  first_image_4_sum[2]/count_C;first_image_4_sum[3] =  first_image_4_sum[3]/count_D;
        LineFitLeastSquares(first_image_4_sum,first_4_sum,4,aa,bb,rr);
        calibration_image(original_p_img_944,calibration_img_944,aa,bb);
        OutFile <<rr<<",";
        //5
        first_image_5_sum[0] =  first_image_5_sum[0]/count_A;first_image_5_sum[1] =  first_image_5_sum[1]/count_B;
        first_image_5_sum[2] =  first_image_5_sum[2]/count_C;first_image_5_sum[3] =  first_image_5_sum[3]/count_D;
        LineFitLeastSquares(first_image_5_sum,first_5_sum,4,aa,bb,rr);
        calibration_image(original_p_img_783,calibration_img_783,aa,bb);
        OutFile <<rr<<",";
        //6
        first_image_6_sum[0] =  first_image_6_sum[0]/count_A;first_image_6_sum[1] =  first_image_6_sum[1]/count_B;
        first_image_6_sum[2] =  first_image_6_sum[2]/count_C;first_image_6_sum[3] =  first_image_6_sum[3]/count_D;
        LineFitLeastSquares(first_image_6_sum,first_6_sum,4,aa,bb,rr);
        calibration_image(original_p_img_796,calibration_img_796,aa,bb);
        OutFile <<rr<<",";
        //7
        first_image_7_sum[0] =  first_image_7_sum[0]/count_A;first_image_7_sum[1] =  first_image_7_sum[1]/count_B;
        first_image_7_sum[2] =  first_image_7_sum[2]/count_C;first_image_7_sum[3] =  first_image_7_sum[3]/count_D;
        LineFitLeastSquares(first_image_7_sum,first_7_sum,4,aa,bb,rr);
        calibration_image(original_p_img_772,calibration_img_772,aa,bb);
        OutFile <<rr<<",";
        //8
        first_image_8_sum[0] =  first_image_8_sum[0]/count_A;first_image_8_sum[1] =  first_image_8_sum[1]/count_B;
        first_image_8_sum[2] =  first_image_8_sum[2]/count_C;first_image_8_sum[3] =  first_image_8_sum[3]/count_D;
        LineFitLeastSquares(first_image_8_sum,first_8_sum,4,aa,bb,rr);
        calibration_image(original_p_img_758,calibration_img_758,aa,bb);
        OutFile <<rr<<",";
        //9
        first_image_9_sum[0] =  first_image_9_sum[0]/count_A;first_image_9_sum[1] =  first_image_9_sum[1]/count_B;
        first_image_9_sum[2] =  first_image_9_sum[2]/count_C;first_image_9_sum[3] =  first_image_9_sum[3]/count_D;
        LineFitLeastSquares(first_image_9_sum,first_9_sum,4,aa,bb,rr);
        calibration_image(original_p_img_665,calibration_img_665,aa,bb);
        OutFile <<rr<<",";

        //10
        first_image_10_sum[0] =  first_image_10_sum[0]/count_A;first_image_10_sum[1] =  first_image_10_sum[1]/count_B;
        first_image_10_sum[2] =  first_image_10_sum[2]/count_C;first_image_10_sum[3] =  first_image_10_sum[3]/count_D;
        LineFitLeastSquares(first_image_10_sum,first_10_sum,4,aa,bb,rr);
        calibration_image(original_p_img_732,calibration_img_732,aa,bb);
        OutFile <<rr<<",";

        //11
        first_image_11_sum[0] =  first_image_11_sum[0]/count_A;first_image_11_sum[1] =  first_image_11_sum[1]/count_B;
        first_image_11_sum[2] =  first_image_11_sum[2]/count_C;first_image_11_sum[3] =  first_image_11_sum[3]/count_D;
        LineFitLeastSquares(first_image_11_sum,first_11_sum,4,aa,bb,rr);
        calibration_image(original_p_img_746,calibration_img_746,aa,bb);
        OutFile <<rr<<",";

        //12
        first_image_12_sum[0] =  first_image_12_sum[0]/count_A;first_image_12_sum[1] =  first_image_12_sum[1]/count_B;
        first_image_12_sum[2] =  first_image_12_sum[2]/count_C;first_image_12_sum[3] =  first_image_12_sum[3]/count_D;
        LineFitLeastSquares(first_image_12_sum,first_12_sum,4,aa,bb,rr);
        calibration_image(original_p_img_720,calibration_img_720,aa,bb);
        OutFile <<rr<<",";

        //13
        first_image_13_sum[0] =  first_image_13_sum[0]/count_A;first_image_13_sum[1] =  first_image_13_sum[1]/count_B;
        first_image_13_sum[2] =  first_image_13_sum[2]/count_C;first_image_13_sum[3] =  first_image_13_sum[3]/count_D;
        LineFitLeastSquares(first_image_13_sum,first_13_sum,4,aa,bb,rr);
        calibration_image(original_p_img_705,calibration_img_705,aa,bb);
        OutFile <<rr<<",";

        //14
        first_image_14_sum[0] =  first_image_14_sum[0]/count_A;first_image_14_sum[1] =  first_image_14_sum[1]/count_B;
        first_image_14_sum[2] =  first_image_14_sum[2]/count_C;first_image_14_sum[3] =  first_image_14_sum[3]/count_D;
        LineFitLeastSquares(first_image_14_sum,first_14_sum,4,aa,bb,rr);
        calibration_image(original_p_img_680,calibration_img_680,aa,bb);
        OutFile <<rr<<",";

        //15
        first_image_15_sum[0] =  first_image_15_sum[0]/count_A;first_image_15_sum[1] =  first_image_15_sum[1]/count_B;
        first_image_15_sum[2] =  first_image_15_sum[2]/count_C;first_image_15_sum[3] =  first_image_15_sum[3]/count_D;
        LineFitLeastSquares(first_image_15_sum,first_15_sum,4,aa,bb,rr);
        calibration_image(original_p_img_919,calibration_img_919,aa,bb);
        OutFile <<rr<<",";

        //16
        first_image_16_sum[0] =  first_image_16_sum[0]/count_A;first_image_16_sum[1] =  first_image_16_sum[1]/count_B;
        first_image_16_sum[2] =  first_image_16_sum[2]/count_C;first_image_16_sum[3] =  first_image_16_sum[3]/count_D;
        LineFitLeastSquares(first_image_16_sum,first_16_sum,4,aa,bb,rr);
        calibration_image(original_p_img_926,calibration_img_926,aa,bb);
        OutFile <<rr<<",";

        //17
        first_image_17_sum[0] =  first_image_17_sum[0]/count_A;first_image_17_sum[1] =  first_image_17_sum[1]/count_B;
        first_image_17_sum[2] =  first_image_17_sum[2]/count_C;first_image_17_sum[3] =  first_image_17_sum[3]/count_D;
        LineFitLeastSquares(first_image_17_sum,first_17_sum,4,aa,bb,rr);
        calibration_image(original_p_img_910,calibration_img_910,aa,bb);
        OutFile <<rr<<",";

        //18
        first_image_18_sum[0] =  first_image_18_sum[0]/count_A;first_image_18_sum[1] =  first_image_18_sum[1]/count_B;
        first_image_18_sum[2] =  first_image_18_sum[2]/count_C;first_image_18_sum[3] =  first_image_18_sum[3]/count_D;
        LineFitLeastSquares(first_image_18_sum,first_18_sum,4,aa,bb,rr);
        calibration_image(original_p_img_902,calibration_img_902,aa,bb);
        OutFile <<rr<<",";

        //19
        first_image_19_sum[0] =  first_image_19_sum[0]/count_A;first_image_19_sum[1] =  first_image_19_sum[1]/count_B;
        first_image_19_sum[2] =  first_image_19_sum[2]/count_C;first_image_19_sum[3] =  first_image_19_sum[3]/count_D;
        LineFitLeastSquares(first_image_19_sum,first_19_sum,4,aa,bb,rr);
        calibration_image(original_p_img_939,calibration_img_939,aa,bb);
        OutFile <<rr<<",";

        //20
        first_image_20_sum[0] =  first_image_20_sum[0]/count_A;first_image_20_sum[1] =  first_image_20_sum[1]/count_B;
        first_image_20_sum[2] =  first_image_20_sum[2]/count_C;first_image_20_sum[3] =  first_image_20_sum[3]/count_D;
        LineFitLeastSquares(first_image_20_sum,first_20_sum,4,aa,bb,rr);
        calibration_image(original_p_img_837,calibration_img_837,aa,bb);
        OutFile <<rr<<",";

        //21
        first_image_21_sum[0] =  first_image_21_sum[0]/count_A;first_image_21_sum[1] =  first_image_21_sum[1]/count_B;
        first_image_21_sum[2] =  first_image_21_sum[2]/count_C;first_image_21_sum[3] =  first_image_21_sum[3]/count_D;
        LineFitLeastSquares(first_image_21_sum,first_21_sum,4,aa,bb,rr);
        calibration_image(original_p_img_848,calibration_img_848,aa,bb);
        OutFile <<rr<<",";

        //22
        first_image_22_sum[0] =  first_image_22_sum[0]/count_A;first_image_22_sum[1] =  first_image_22_sum[1]/count_B;
        first_image_22_sum[2] =  first_image_22_sum[2]/count_C;first_image_22_sum[3] =  first_image_22_sum[3]/count_D;
        LineFitLeastSquares(first_image_22_sum,first_22_sum,4,aa,bb,rr);
        calibration_image(original_p_img_827,calibration_img_827,aa,bb);
        OutFile <<rr<<",";

        //23
        first_image_23_sum[0] =  first_image_23_sum[0]/count_A;first_image_23_sum[1] =  first_image_23_sum[1]/count_B;
        first_image_23_sum[2] =  first_image_23_sum[2]/count_C;first_image_23_sum[3] =  first_image_23_sum[3]/count_D;
        LineFitLeastSquares(first_image_23_sum,first_23_sum,4,aa,bb,rr);
        calibration_image(original_p_img_815,calibration_img_815,aa,bb);
        OutFile <<rr<<",";

        //24
        first_image_24_sum[0] =  first_image_24_sum[0]/count_A;first_image_24_sum[1] =  first_image_24_sum[1]/count_B;
        first_image_24_sum[2] =  first_image_24_sum[2]/count_C;first_image_24_sum[3] =  first_image_24_sum[3]/count_D;
        LineFitLeastSquares(first_image_24_sum,first_24_sum,4,aa,bb,rr);
        calibration_image(original_p_img_934,calibration_img_934,aa,bb);
        OutFile <<rr<<",";
        OutFile.close();

    }
    //四等级灰度板中 0.99等级的灰度板图像点击返回函数;
    //event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号
    void Hyperspectralimage::on_mouse1(int event, int x, int y)
    {
        if (event == EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处打点
        {
            Point  p = Point(x, y);

            first_image_0_sum[0] = first_image_0_sum[0] + float(original_w_img_877.at<uchar>(y, x));
            first_image_1_sum[0] = first_image_1_sum[0] + float(original_w_img_886.at<uchar>(y, x));
            first_image_2_sum[0] = first_image_2_sum[0] + float(original_w_img_869.at<uchar>(y, x));
            first_image_3_sum[0] = first_image_3_sum[0] + float(original_w_img_858.at<uchar>(y, x));
            first_image_4_sum[0] = first_image_4_sum[0] + float(original_w_img_944.at<uchar>(y, x));
            first_image_5_sum[0] = first_image_5_sum[0] + float(original_w_img_783.at<uchar>(y, x));
            first_image_6_sum[0] = first_image_6_sum[0] + float(original_w_img_796.at<uchar>(y, x));
            first_image_7_sum[0] = first_image_7_sum[0] + float(original_w_img_772.at<uchar>(y, x));
            first_image_8_sum[0] = first_image_8_sum[0] + float(original_w_img_758.at<uchar>(y, x));
            first_image_9_sum[0] = first_image_9_sum[0] + float(original_w_img_665.at<uchar>(y, x));
            first_image_10_sum[0] = first_image_10_sum[0] + float(original_w_img_732.at<uchar>(y, x));
            first_image_11_sum[0] = first_image_11_sum[0] + float(original_w_img_746.at<uchar>(y, x));
            first_image_12_sum[0] = first_image_12_sum[0] + float(original_w_img_720.at<uchar>(y, x));
            first_image_13_sum[0] = first_image_13_sum[0] + float(original_w_img_705.at<uchar>(y, x));
            first_image_14_sum[0] = first_image_14_sum[0] + float(original_w_img_680.at<uchar>(y, x));
            first_image_15_sum[0] = first_image_15_sum[0] + float(original_w_img_919.at<uchar>(y, x));
            first_image_16_sum[0] = first_image_16_sum[0] + float(original_w_img_926.at<uchar>(y, x));
            first_image_17_sum[0] = first_image_17_sum[0] + float(original_w_img_910.at<uchar>(y, x));
            first_image_18_sum[0] = first_image_18_sum[0] + float(original_w_img_902.at<uchar>(y, x));
            first_image_19_sum[0] = first_image_19_sum[0] + float(original_w_img_939.at<uchar>(y, x));
            first_image_20_sum[0] = first_image_20_sum[0] + float(original_w_img_837.at<uchar>(y, x));
            first_image_21_sum[0] = first_image_21_sum[0] + float(original_w_img_848.at<uchar>(y, x));
            first_image_22_sum[0] = first_image_22_sum[0] + float(original_w_img_827.at<uchar>(y, x));
            first_image_23_sum[0] = first_image_23_sum[0] + float(original_w_img_815.at<uchar>(y, x));
            first_image_24_sum[0] = first_image_24_sum[0] + float(original_w_img_934.at<uchar>(y, x));

            count_A++;
            circle(white_image_A, p, 1, 255, -1);
            imshow("white_image_A", white_image_A);
            cout << "white_image_A:" << count_A << endl;
        }
    }

    //四等级灰度板中 0.5等级的灰度板图像点击返回函数;
    void Hyperspectralimage::on_mouse2(int event, int x, int y)
    {
        if (event == EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处打点
        {
            Point  p = Point(x, y);

            first_image_0_sum[1] = first_image_0_sum[1] + float(original_w_img_877.at<uchar>(y, x));
            first_image_1_sum[1] = first_image_1_sum[1] + float(original_w_img_886.at<uchar>(y, x));
            first_image_2_sum[1] = first_image_2_sum[1] + float(original_w_img_869.at<uchar>(y, x));
            first_image_3_sum[1] = first_image_3_sum[1] + float(original_w_img_858.at<uchar>(y, x));
            first_image_4_sum[1] = first_image_4_sum[1] + float(original_w_img_944.at<uchar>(y, x));
            first_image_5_sum[1] = first_image_5_sum[1] + float(original_w_img_783.at<uchar>(y, x));
            first_image_6_sum[1] = first_image_6_sum[1] + float(original_w_img_796.at<uchar>(y, x));
            first_image_7_sum[1] = first_image_7_sum[1] + float(original_w_img_772.at<uchar>(y, x));
            first_image_8_sum[1] = first_image_8_sum[1] + float(original_w_img_758.at<uchar>(y, x));
            first_image_9_sum[1] = first_image_9_sum[1] + float(original_w_img_665.at<uchar>(y, x));
            first_image_10_sum[1] = first_image_10_sum[1] + float(original_w_img_732.at<uchar>(y, x));
            first_image_11_sum[1] = first_image_11_sum[1] + float(original_w_img_746.at<uchar>(y, x));
            first_image_12_sum[1] = first_image_12_sum[1] + float(original_w_img_720.at<uchar>(y, x));
            first_image_13_sum[1] = first_image_13_sum[1] + float(original_w_img_705.at<uchar>(y, x));
            first_image_14_sum[1] = first_image_14_sum[1] + float(original_w_img_680.at<uchar>(y, x));
            first_image_15_sum[1] = first_image_15_sum[1] + float(original_w_img_919.at<uchar>(y, x));
            first_image_16_sum[1] = first_image_16_sum[1] + float(original_w_img_926.at<uchar>(y, x));
            first_image_17_sum[1] = first_image_17_sum[1] + float(original_w_img_910.at<uchar>(y, x));
            first_image_18_sum[1] = first_image_18_sum[1] + float(original_w_img_902.at<uchar>(y, x));
            first_image_19_sum[1] = first_image_19_sum[1] + float(original_w_img_939.at<uchar>(y, x));
            first_image_20_sum[1] = first_image_20_sum[1] + float(original_w_img_837.at<uchar>(y, x));
            first_image_21_sum[1] = first_image_21_sum[1] + float(original_w_img_848.at<uchar>(y, x));
            first_image_22_sum[1] = first_image_22_sum[1] + float(original_w_img_827.at<uchar>(y, x));
            first_image_23_sum[1] = first_image_23_sum[1] + float(original_w_img_815.at<uchar>(y, x));
            first_image_24_sum[1] = first_image_24_sum[1] + float(original_w_img_934.at<uchar>(y, x));

            circle(white_image_B, p, 1, 255, -1);
            imshow("white_image_B", white_image_B);
            count_B++;
            cout << "white_image_B" << count_B << endl;
        }
    }

    //四等级灰度板中 0.25等级的灰度板图像点击返回函数;
    void Hyperspectralimage::on_mouse3(int event, int x, int y) //event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号
    {
        if (event == EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处打点
        {
            Point  p = Point(x, y);

            first_image_0_sum[2] = first_image_0_sum[2] + float(original_w_img_877.at<uchar>(y, x));
            first_image_1_sum[2] = first_image_1_sum[2] + float(original_w_img_886.at<uchar>(y, x));
            first_image_2_sum[2] = first_image_2_sum[2] + float(original_w_img_869.at<uchar>(y, x));
            first_image_3_sum[2] = first_image_3_sum[2] + float(original_w_img_858.at<uchar>(y, x));
            first_image_4_sum[2] = first_image_4_sum[2] + float(original_w_img_944.at<uchar>(y, x));
            first_image_5_sum[2] = first_image_5_sum[2] + float(original_w_img_783.at<uchar>(y, x));
            first_image_6_sum[2] = first_image_6_sum[2] + float(original_w_img_796.at<uchar>(y, x));
            first_image_7_sum[2] = first_image_7_sum[2] + float(original_w_img_772.at<uchar>(y, x));
            first_image_8_sum[2] = first_image_8_sum[2] + float(original_w_img_758.at<uchar>(y, x));
            first_image_9_sum[2] = first_image_9_sum[2] + float(original_w_img_665.at<uchar>(y, x));
            first_image_10_sum[2] = first_image_10_sum[2] + float(original_w_img_732.at<uchar>(y, x));
            first_image_11_sum[2] = first_image_11_sum[2] + float(original_w_img_746.at<uchar>(y, x));
            first_image_12_sum[2] = first_image_12_sum[2] + float(original_w_img_720.at<uchar>(y, x));
            first_image_13_sum[2] = first_image_13_sum[2] + float(original_w_img_705.at<uchar>(y, x));
            first_image_14_sum[2] = first_image_14_sum[2] + float(original_w_img_680.at<uchar>(y, x));
            first_image_15_sum[2] = first_image_15_sum[2] + float(original_w_img_919.at<uchar>(y, x));
            first_image_16_sum[2] = first_image_16_sum[2] + float(original_w_img_926.at<uchar>(y, x));
            first_image_17_sum[2] = first_image_17_sum[2] + float(original_w_img_910.at<uchar>(y, x));
            first_image_18_sum[2] = first_image_18_sum[2] + float(original_w_img_902.at<uchar>(y, x));
            first_image_19_sum[2] = first_image_19_sum[2] + float(original_w_img_939.at<uchar>(y, x));
            first_image_20_sum[2] = first_image_20_sum[2] + float(original_w_img_837.at<uchar>(y, x));
            first_image_21_sum[2] = first_image_21_sum[2] + float(original_w_img_848.at<uchar>(y, x));
            first_image_22_sum[2] = first_image_22_sum[2] + float(original_w_img_827.at<uchar>(y, x));
            first_image_23_sum[2] = first_image_23_sum[2] + float(original_w_img_815.at<uchar>(y, x));
            first_image_24_sum[2] = first_image_24_sum[2] + float(original_w_img_934.at<uchar>(y, x));


            count_C++;
            circle(white_image_C, p, 1, 255, -1);
            imshow("white_image_C", white_image_C);
            cout << "white_image_C" << count_C << endl;
        }
    }

    //四等级灰度板中 0.1等级的灰度板图像点击返回函数;
    void Hyperspectralimage::on_mouse4(int event, int x, int y)
    {
        if (event == EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处打点
        {
            Point  p = Point(x, y);

            first_image_0_sum[3] = first_image_0_sum[3] + float(original_w_img_877.at<uchar>(y, x));
            first_image_1_sum[3] = first_image_1_sum[3] + float(original_w_img_886.at<uchar>(y, x));
            first_image_2_sum[3] = first_image_2_sum[3] + float(original_w_img_869.at<uchar>(y, x));
            first_image_3_sum[3] = first_image_3_sum[3] + float(original_w_img_858.at<uchar>(y, x));
            first_image_4_sum[3] = first_image_4_sum[3] + float(original_w_img_944.at<uchar>(y, x));
            first_image_5_sum[3] = first_image_5_sum[3] + float(original_w_img_783.at<uchar>(y, x));
            first_image_6_sum[3] = first_image_6_sum[3] + float(original_w_img_796.at<uchar>(y, x));
            first_image_7_sum[3] = first_image_7_sum[3] + float(original_w_img_772.at<uchar>(y, x));
            first_image_8_sum[3] = first_image_8_sum[3] + float(original_w_img_758.at<uchar>(y, x));
            first_image_9_sum[3] = first_image_9_sum[3] + float(original_w_img_665.at<uchar>(y, x));
            first_image_10_sum[3] = first_image_10_sum[3] + float(original_w_img_732.at<uchar>(y, x));
            first_image_11_sum[3] = first_image_11_sum[3] + float(original_w_img_746.at<uchar>(y, x));
            first_image_12_sum[3] = first_image_12_sum[3] + float(original_w_img_720.at<uchar>(y, x));
            first_image_13_sum[3] = first_image_13_sum[3] + float(original_w_img_705.at<uchar>(y, x));
            first_image_14_sum[3] = first_image_14_sum[3] + float(original_w_img_680.at<uchar>(y, x));
            first_image_15_sum[3] = first_image_15_sum[3] + float(original_w_img_919.at<uchar>(y, x));
            first_image_16_sum[3] = first_image_16_sum[3] + float(original_w_img_926.at<uchar>(y, x));
            first_image_17_sum[3] = first_image_17_sum[3] + float(original_w_img_910.at<uchar>(y, x));
            first_image_18_sum[3] = first_image_18_sum[3] + float(original_w_img_902.at<uchar>(y, x));
            first_image_19_sum[3] = first_image_19_sum[3] + float(original_w_img_939.at<uchar>(y, x));
            first_image_20_sum[3] = first_image_20_sum[3] + float(original_w_img_837.at<uchar>(y, x));
            first_image_21_sum[3] = first_image_21_sum[3] + float(original_w_img_848.at<uchar>(y, x));
            first_image_22_sum[3] = first_image_22_sum[3] + float(original_w_img_827.at<uchar>(y, x));
            first_image_23_sum[3] = first_image_23_sum[3] + float(original_w_img_815.at<uchar>(y, x));
            first_image_24_sum[3] = first_image_24_sum[3] + float(original_w_img_934.at<uchar>(y, x));

            circle(white_image_D, p, 1, 255, -1);
            imshow("white_image_D", white_image_D);
            count_D++;
            std::cout << "white_image_D" << count_D << endl;
        }
    }
    void Hyperspectralimage::LineFitLeastSquares(float *data_x, float *data_y, int data_n, float &Result_a, float &Result_b, float &Result_rr)
    {
        float A = 0.0;
        float B = 0.0;
        float C = 0.0;
        float D = 0.0;
        float E = 0.0;
        float F = 0.0;

        for (int i=0; i<data_n; i++)
        {
            A += data_x[i] * data_x[i];
            B += data_x[i];
            C += data_x[i] * data_y[i];
            D += data_y[i];
        }

        // 计算斜率a和截距b
        float a, b, temp = 0;
        if( temp = (data_n*A - B*B) )// 判断分母不为0
        {
            a = (data_n*C - B*D) / temp;
            b = (A*D - B*C) / temp;
        }
        else
        {
            a = 1;
            b = 0;
        }

        // 计算相关系数r
        float Xmean, Ymean;
        Xmean = B / data_n;
        Ymean = D / data_n;

        float tempSumXX = 0.0, tempSumYY = 0.0;
        for (int i=0; i<data_n; i++)
        {
            tempSumXX += (data_x[i] - Xmean) * (data_x[i] - Xmean);
            tempSumYY += (data_y[i] - Ymean) * (data_y[i] - Ymean);
            E += (data_x[i] - Xmean) * (data_y[i] - Ymean);
        }
        F = sqrt(tempSumXX) * sqrt(tempSumYY);

        float r;
        r = E / F;

        Result_a = a;
        Result_b = b;
        Result_rr = r * r;
    }
    void Hyperspectralimage::calibration_image(Mat& inputImage,Mat& ouputImage, float a, float b)
    {
        int rowNumber = inputImage.rows;  //行数
        int colNumber = inputImage.cols;  //列数

        float c,d;
        c = ( 0 - b ) / a ;
        d = ( 1 - b ) / a ;

        for (int i = 0; i < rowNumber; i++)
        {
            for (int j = 0; j < colNumber; j++)
            {
                if(inputImage.at<uchar>(i, j) <= c)
                {
                    ouputImage.at<uchar>(i, j) = 0;
                }
                else if(inputImage.at<uchar>(i, j) >= d)
                {
                    ouputImage.at<uchar>(i, j) = 255;
                }
                else
                {
                    ouputImage.at<uchar>(i, j) = int (255 * ( a * inputImage.at<uchar>(i, j) + b ) );
                }
            }
        }
    }
    void Hyperspectralimage::rebuildallimage()
    {
        rebuildoriginalimage(original_p_img_877,0,0);
        rebuildoriginalimage(original_p_img_886,0,1);
        rebuildoriginalimage(original_p_img_869,0,2);
        rebuildoriginalimage(original_p_img_858,0,3);
        rebuildoriginalimage(original_p_img_944,0,4);
        rebuildoriginalimage(original_p_img_783,1,0);
        rebuildoriginalimage(original_p_img_796,1,1);
        rebuildoriginalimage(original_p_img_772,1,2);
        rebuildoriginalimage(original_p_img_758,1,3);
        rebuildoriginalimage(original_p_img_665,1,4);
        rebuildoriginalimage(original_p_img_732,2,0);
        rebuildoriginalimage(original_p_img_746,2,1);
        rebuildoriginalimage(original_p_img_720,2,2);
        rebuildoriginalimage(original_p_img_705,2,3);
        rebuildoriginalimage(original_p_img_680,2,4);
        rebuildoriginalimage(original_p_img_919,3,0);
        rebuildoriginalimage(original_p_img_926,3,1);
        rebuildoriginalimage(original_p_img_910,3,2);
        rebuildoriginalimage(original_p_img_902,3,3);
        rebuildoriginalimage(original_p_img_939,3,4);
        rebuildoriginalimage(original_p_img_837,4,0);
        rebuildoriginalimage(original_p_img_848,4,1);
        rebuildoriginalimage(original_p_img_827,4,2);
        rebuildoriginalimage(original_p_img_815,4,3);
        rebuildoriginalimage(original_p_img_934,4,4);

        rebuildwhiteimage(original_w_img_877,0,0);
        rebuildwhiteimage(original_w_img_886,0,1);
        rebuildwhiteimage(original_w_img_869,0,2);
        rebuildwhiteimage(original_w_img_858,0,3);
        rebuildwhiteimage(original_w_img_944,0,4);
        rebuildwhiteimage(original_w_img_783,1,0);
        rebuildwhiteimage(original_w_img_796,1,1);
        rebuildwhiteimage(original_w_img_772,1,2);
        rebuildwhiteimage(original_w_img_758,1,3);
        rebuildwhiteimage(original_w_img_665,1,4);
        rebuildwhiteimage(original_w_img_732,2,0);
        rebuildwhiteimage(original_w_img_746,2,1);
        rebuildwhiteimage(original_w_img_720,2,2);
        rebuildwhiteimage(original_w_img_705,2,3);
        rebuildwhiteimage(original_w_img_680,2,4);
        rebuildwhiteimage(original_w_img_919,3,0);
        rebuildwhiteimage(original_w_img_926,3,1);
        rebuildwhiteimage(original_w_img_910,3,2);
        rebuildwhiteimage(original_w_img_902,3,3);
        rebuildwhiteimage(original_w_img_939,3,4);
        rebuildwhiteimage(original_w_img_837,4,0);
        rebuildwhiteimage(original_w_img_848,4,1);
        rebuildwhiteimage(original_w_img_827,4,2);
        rebuildwhiteimage(original_w_img_815,4,3);
        rebuildwhiteimage(original_w_img_934,4,4);

        white_image_A = original_p_img_877.clone();
        white_image_B = original_p_img_877.clone();
        white_image_C = original_p_img_877.clone();
        white_image_D = original_p_img_877.clone();
    }

	void Hyperspectralimage::rebuildoriginalimage(Mat& output_image,int x,int y)
	{
        int row, col;
        for (int i = 0; i < rowNumber; i++)
        {
            row = x + i * passageNumber;
            for (int j = 0; j < colNumber; j++)
            {
                col = y + j * passageNumber;
                output_image.at<uchar>(i, j) = Image.at<uchar>(row, col);
            }
        }
	}
    void Hyperspectralimage::rebuildwhiteimage(Mat& output_image,int x,int y)
    {
        int row, col;
        for (int i = 0; i < rowNumber; i++)
        {
            row = x + i * passageNumber;
            for (int j = 0; j < colNumber; j++)
            {
                col = y + j * passageNumber;
                output_image.at<uchar>(i, j) = WhiteIamge.at<uchar>(row, col);
            }
        }
    }

	void Hyperspectralimage::createallimages()
	{
        original_p_img_877.create(rowNumber, colNumber, CV_8UC1);       //877.940nm
        original_p_img_886.create(rowNumber, colNumber, CV_8UC1);       //886.689nm
        original_p_img_869.create(rowNumber, colNumber, CV_8UC1);       //869.256nm
        original_p_img_858.create(rowNumber, colNumber, CV_8UC1);       //858.490nm
        original_p_img_944.create(rowNumber, colNumber, CV_8UC1);       //944.466nm
        original_p_img_783.create(rowNumber, colNumber, CV_8UC1);       //783.508nm
        original_p_img_796.create(rowNumber, colNumber, CV_8UC1);       //796.428nm
        original_p_img_772.create(rowNumber, colNumber, CV_8UC1);       //772.240nm
        original_p_img_758.create(rowNumber, colNumber, CV_8UC1);       //758.962nm
        original_p_img_665.create(rowNumber, colNumber, CV_8UC1);       //665.883nm
        original_p_img_732.create(rowNumber, colNumber, CV_8UC1);       //732.043nm
        original_p_img_746.create(rowNumber, colNumber, CV_8UC1);       //746.304nm
        original_p_img_720.create(rowNumber, colNumber, CV_8UC1);       //720.119nm
        original_p_img_705.create(rowNumber, colNumber, CV_8UC1);       //705.457nm
        original_p_img_680.create(rowNumber, colNumber, CV_8UC1);       //680.543nm
        original_p_img_919.create(rowNumber, colNumber, CV_8UC1);       //919.833nm
        original_p_img_926.create(rowNumber, colNumber, CV_8UC1);       //926.032nm
        original_p_img_910.create(rowNumber, colNumber, CV_8UC1);       //910.186nm
        original_p_img_902.create(rowNumber, colNumber, CV_8UC1);       //902.089nm
        original_p_img_939.create(rowNumber, colNumber, CV_8UC1);       //939.834nm
        original_p_img_837.create(rowNumber, colNumber, CV_8UC1);       //837.423nm
        original_p_img_848.create(rowNumber, colNumber, CV_8UC1);       //848.456nm
        original_p_img_827.create(rowNumber, colNumber, CV_8UC1);       //827.127nm
        original_p_img_815.create(rowNumber, colNumber, CV_8UC1);       //815.456nm
        original_p_img_934.create(rowNumber, colNumber, CV_8UC1);       //934.769nm

        original_w_img_877.create(rowNumber, colNumber, CV_8UC1);       //877.940nm
        original_w_img_886.create(rowNumber, colNumber, CV_8UC1);       //886.689nm
        original_w_img_869.create(rowNumber, colNumber, CV_8UC1);       //869.256nm
        original_w_img_858.create(rowNumber, colNumber, CV_8UC1);       //858.490nm
        original_w_img_944.create(rowNumber, colNumber, CV_8UC1);       //944.466nm
        original_w_img_783.create(rowNumber, colNumber, CV_8UC1);       //783.508nm
        original_w_img_796.create(rowNumber, colNumber, CV_8UC1);       //796.428nm
        original_w_img_772.create(rowNumber, colNumber, CV_8UC1);       //772.240nm
        original_w_img_758.create(rowNumber, colNumber, CV_8UC1);       //758.962nm
        original_w_img_665.create(rowNumber, colNumber, CV_8UC1);       //665.883nm
        original_w_img_732.create(rowNumber, colNumber, CV_8UC1);       //732.043nm
        original_w_img_746.create(rowNumber, colNumber, CV_8UC1);       //746.304nm
        original_w_img_720.create(rowNumber, colNumber, CV_8UC1);       //720.119nm
        original_w_img_705.create(rowNumber, colNumber, CV_8UC1);       //705.457nm
        original_w_img_680.create(rowNumber, colNumber, CV_8UC1);       //680.543nm
        original_w_img_919.create(rowNumber, colNumber, CV_8UC1);       //919.833nm
        original_w_img_926.create(rowNumber, colNumber, CV_8UC1);       //926.032nm
        original_w_img_910.create(rowNumber, colNumber, CV_8UC1);       //910.186nm
        original_w_img_902.create(rowNumber, colNumber, CV_8UC1);       //902.089nm
        original_w_img_939.create(rowNumber, colNumber, CV_8UC1);       //939.834nm
        original_w_img_837.create(rowNumber, colNumber, CV_8UC1);       //837.423nm
        original_w_img_848.create(rowNumber, colNumber, CV_8UC1);       //848.456nm
        original_w_img_827.create(rowNumber, colNumber, CV_8UC1);       //827.127nm
        original_w_img_815.create(rowNumber, colNumber, CV_8UC1);       //815.456nm
        original_w_img_934.create(rowNumber, colNumber, CV_8UC1);       //934.769nm

        calibration_img_877.create(rowNumber, colNumber, CV_8UC1);       //877.940nm
        calibration_img_886.create(rowNumber, colNumber, CV_8UC1);       //886.689nm
        calibration_img_869.create(rowNumber, colNumber, CV_8UC1);       //869.256nm
        calibration_img_858.create(rowNumber, colNumber, CV_8UC1);       //858.490nm
        calibration_img_944.create(rowNumber, colNumber, CV_8UC1);       //944.466nm
        calibration_img_783.create(rowNumber, colNumber, CV_8UC1);       //783.508nm
        calibration_img_796.create(rowNumber, colNumber, CV_8UC1);       //796.428nm
        calibration_img_772.create(rowNumber, colNumber, CV_8UC1);       //772.240nm
        calibration_img_758.create(rowNumber, colNumber, CV_8UC1);       //758.962nm
        calibration_img_665.create(rowNumber, colNumber, CV_8UC1);       //665.883nm
        calibration_img_732.create(rowNumber, colNumber, CV_8UC1);       //732.043nm
        calibration_img_746.create(rowNumber, colNumber, CV_8UC1);       //746.304nm
        calibration_img_720.create(rowNumber, colNumber, CV_8UC1);       //720.119nm
        calibration_img_705.create(rowNumber, colNumber, CV_8UC1);       //705.457nm
        calibration_img_680.create(rowNumber, colNumber, CV_8UC1);       //680.543nm
        calibration_img_919.create(rowNumber, colNumber, CV_8UC1);       //919.833nm
        calibration_img_926.create(rowNumber, colNumber, CV_8UC1);       //926.032nm
        calibration_img_910.create(rowNumber, colNumber, CV_8UC1);       //910.186nm
        calibration_img_902.create(rowNumber, colNumber, CV_8UC1);       //902.089nm
        calibration_img_939.create(rowNumber, colNumber, CV_8UC1);       //939.834nm
        calibration_img_837.create(rowNumber, colNumber, CV_8UC1);       //837.423nm
        calibration_img_848.create(rowNumber, colNumber, CV_8UC1);       //848.456nm
        calibration_img_827.create(rowNumber, colNumber, CV_8UC1);       //827.127nm
        calibration_img_815.create(rowNumber, colNumber, CV_8UC1);       //815.456nm
        calibration_img_934.create(rowNumber, colNumber, CV_8UC1);       //934.769nm
		std::cout << "Create all Images!" << std::endl;
	}
	
	void Hyperspectralimage::saveallimages(string filename)
	{
        cv::imwrite(filename+"first_image_0"+".bmp", original_p_img_877);
        cv::imwrite(filename+"first_image_1"+".bmp", original_p_img_886);
        cv::imwrite(filename+"first_image_2"+".bmp", original_p_img_869);
        cv::imwrite(filename+"first_image_3"+".bmp", original_p_img_858);
        cv::imwrite(filename+"first_image_4"+".bmp", original_p_img_944);
        cv::imwrite(filename+"first_image_5"+".bmp", original_p_img_783);
        cv::imwrite(filename+"first_image_6"+".bmp", original_p_img_796);
        cv::imwrite(filename+"first_image_7"+".bmp", original_p_img_772);
        cv::imwrite(filename+"first_image_8"+".bmp", original_p_img_758);
        cv::imwrite(filename+"first_image_9"+".bmp", original_p_img_665);
        cv::imwrite(filename+"first_image_10"+".bmp", original_p_img_732);
        cv::imwrite(filename+"first_image_11"+".bmp", original_p_img_746);
        cv::imwrite(filename+"first_image_12"+".bmp", original_p_img_720);
        cv::imwrite(filename+"first_image_13"+".bmp", original_p_img_705);
        cv::imwrite(filename+"first_image_14"+".bmp", original_p_img_680);
        cv::imwrite(filename+"first_image_15"+".bmp", original_p_img_919);
        cv::imwrite(filename+"first_image_16"+".bmp", original_p_img_926);
        cv::imwrite(filename+"first_image_17"+".bmp", original_p_img_910);
        cv::imwrite(filename+"first_image_18"+".bmp", original_p_img_902);
        cv::imwrite(filename+"first_image_19"+".bmp", original_p_img_939);
        cv::imwrite(filename+"first_image_20"+".bmp", original_p_img_837);
        cv::imwrite(filename+"first_image_21"+".bmp", original_p_img_848);
        cv::imwrite(filename+"first_image_22"+".bmp", original_p_img_827);
        cv::imwrite(filename+"first_image_23"+".bmp", original_p_img_815);
        cv::imwrite(filename+"first_image_24"+".bmp", original_p_img_934);

        cv::imwrite(filename+"first_white_image_0"+".bmp", original_w_img_877);
        cv::imwrite(filename+"first_white_image_1"+".bmp", original_w_img_886);
        cv::imwrite(filename+"first_white_image_2"+".bmp", original_w_img_869);
        cv::imwrite(filename+"first_white_image_3"+".bmp", original_w_img_858);
        cv::imwrite(filename+"first_white_image_4"+".bmp", original_w_img_944);
        cv::imwrite(filename+"first_white_image_5"+".bmp", original_w_img_783);
        cv::imwrite(filename+"first_white_image_6"+".bmp", original_w_img_796);
        cv::imwrite(filename+"first_white_image_7"+".bmp", original_w_img_772);
        cv::imwrite(filename+"first_white_image_8"+".bmp", original_w_img_758);
        cv::imwrite(filename+"first_white_image_9"+".bmp", original_w_img_665);
        cv::imwrite(filename+"first_white_image_10"+".bmp", original_w_img_732);
        cv::imwrite(filename+"first_white_image_11"+".bmp", original_w_img_746);
        cv::imwrite(filename+"first_white_image_12"+".bmp", original_w_img_720);
        cv::imwrite(filename+"first_white_image_13"+".bmp", original_w_img_705);
        cv::imwrite(filename+"first_white_image_14"+".bmp", original_w_img_680);
        cv::imwrite(filename+"first_white_image_15"+".bmp", original_w_img_919);
        cv::imwrite(filename+"first_white_image_16"+".bmp", original_w_img_926);
        cv::imwrite(filename+"first_white_image_17"+".bmp", original_w_img_910);
        cv::imwrite(filename+"first_white_image_18"+".bmp", original_w_img_902);
        cv::imwrite(filename+"first_white_image_19"+".bmp", original_w_img_939);
        cv::imwrite(filename+"first_white_image_20"+".bmp", original_w_img_837);
        cv::imwrite(filename+"first_white_image_21"+".bmp", original_w_img_848);
        cv::imwrite(filename+"first_white_image_22"+".bmp", original_w_img_827);
        cv::imwrite(filename+"first_white_image_23"+".bmp", original_w_img_815);
        cv::imwrite(filename+"first_white_image_24"+".bmp", original_w_img_934);

        cv::imwrite(filename+"first_calibration_image_0"+".bmp", calibration_img_877);
        cv::imwrite(filename+"first_calibration_image_1"+".bmp", calibration_img_886);
        cv::imwrite(filename+"first_calibration_image_2"+".bmp", calibration_img_869);
        cv::imwrite(filename+"first_calibration_image_3"+".bmp", calibration_img_858);
        cv::imwrite(filename+"first_calibration_image_4"+".bmp", calibration_img_944);
        cv::imwrite(filename+"first_calibration_image_5"+".bmp", calibration_img_783);
        cv::imwrite(filename+"first_calibration_image_6"+".bmp", calibration_img_796);
        cv::imwrite(filename+"first_calibration_image_7"+".bmp", calibration_img_772);
        cv::imwrite(filename+"first_calibration_image_8"+".bmp", calibration_img_758);
        cv::imwrite(filename+"first_calibration_image_9"+".bmp", calibration_img_665);
        cv::imwrite(filename+"first_calibration_image_10"+".bmp", calibration_img_732);
        cv::imwrite(filename+"first_calibration_image_11"+".bmp", calibration_img_746);
        cv::imwrite(filename+"first_calibration_image_12"+".bmp", calibration_img_720);
        cv::imwrite(filename+"first_calibration_image_13"+".bmp", calibration_img_705);
        cv::imwrite(filename+"first_calibration_image_14"+".bmp", calibration_img_680);
        cv::imwrite(filename+"first_calibration_image_15"+".bmp", calibration_img_919);
        cv::imwrite(filename+"first_calibration_image_16"+".bmp", calibration_img_926);
        cv::imwrite(filename+"first_calibration_image_17"+".bmp", calibration_img_910);
        cv::imwrite(filename+"first_calibration_image_18"+".bmp", calibration_img_902);
        cv::imwrite(filename+"first_calibration_image_19"+".bmp", calibration_img_939);
        cv::imwrite(filename+"first_calibration_image_20"+".bmp", calibration_img_837);
        cv::imwrite(filename+"first_calibration_image_21"+".bmp", calibration_img_848);
        cv::imwrite(filename+"first_calibration_image_22"+".bmp", calibration_img_827);
        cv::imwrite(filename+"first_calibration_image_23"+".bmp", calibration_img_815);
        cv::imwrite(filename+"first_calibration_image_24"+".bmp", calibration_img_934);
		std::cout << "Save all Images!" << std::endl;		
	}
}