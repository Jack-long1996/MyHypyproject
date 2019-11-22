//
// Created by ubuntu on 11/1/19.
//

#ifndef HYPERSPECTRALIMAGE_H
#define HYPERSPECTRALIMAGE_H

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace Himage{
    class Hyperspectralimage{
    public:
        Hyperspectralimage(string opfilename,string owfilename,string rgbfilename);
        ~Hyperspectralimage();
        void rebuildoriginalimage(Mat& output_image,int x,int y);
        void rebuildwhiteimage(Mat& output_image,int x,int y);
        void rebuildallimage();
		void createallimages();
		void saveallimages(string filename);
        void LineFitLeastSquares(float *data_x, float *data_y, int data_n, float &Result_a, float &Result_b, float &Result_rr);
        void calibration_image(Mat& inputImage,Mat& ouputImage, float a, float b);
        void calibrationallimage();
        void on_mouse4(int event, int x, int y);
        void on_mouse3(int event, int x, int y);
        void on_mouse2(int event, int x, int y);
        void on_mouse1(int event, int x, int y);

        void on_mouse5(int event, int x, int y);
        void on_mouse6(int event, int x, int y);
        void StartImageregistration(string reffilename,string srcfilename);
        void Image_registration();
        void Image_allregistration();

    public:
        Mat white_image_A, white_image_B, white_image_C, white_image_D;
        //Mat white_image_A 表示四等级灰度板中 0.99等级的灰度板图像;
        //Mat white_image_B 表示四等级灰度板中 0.5等级的灰度板图像;
        //Mat white_image_C 表示四等级灰度板中 0.25等级的灰度板图像;
        //Mat white_image_D 表示四等级灰度板中 0.1等级的灰度板图像;
        Mat ref_win, src_win;
        string xmlwritefilename;
        string xmlreadfilename;
        string pattern_bmp;

    private:
		int rowNumber;  //行数
		int colNumber;  //列数
		int passageNumber;//通道数
        ofstream OutFile;

        int count_A;//count_A 表示四等级灰度板中 0.99等级的灰度板图像中的打点个数;
        int count_B;//count_B 表示四等级灰度板中 0.5等级的灰度板图像中的打点个数;
        int count_C;//count_C 表示四等级灰度板中 0.25等级的灰度板图像中的打点个数;
        int count_D;//count_D 表示四等级灰度板中 0.1等级的灰度板图像中的打点个数;

        vector<Point2f> imagePoints1, imagePoints2;
        int pcount = 0;

        Mat Image;
		Mat WhiteIamge;
		Mat RGBImage;
        Mat original_p_img_877;       //877.940nm
        Mat original_p_img_886;       //886.689nm
        Mat original_p_img_869;       //869.256nm
        Mat original_p_img_858;       //858.490nm
        Mat original_p_img_944;       //944.466nm
        Mat original_p_img_783;       //783.508nm
        Mat original_p_img_796;       //796.428nm
        Mat original_p_img_772;       //772.240nm
        Mat original_p_img_758;       //758.962nm
        Mat original_p_img_665;       //665.883nm
        Mat original_p_img_732;       //732.043nm
        Mat original_p_img_746;       //746.304nm
        Mat original_p_img_720;       //720.119nm
        Mat original_p_img_705;       //705.457nm
        Mat original_p_img_680;       //680.543nm
        Mat original_p_img_919;       //919.833nm
        Mat original_p_img_926;       //926.032nm
        Mat original_p_img_910;       //910.186nm
        Mat original_p_img_902;       //902.089nm
        Mat original_p_img_939;       //939.834nm
        Mat original_p_img_837;       //837.423nm
        Mat original_p_img_848;       //848.456nm
        Mat original_p_img_827;       //827.127nm
        Mat original_p_img_815;       //815.456nm
        Mat original_p_img_934;       //934.769nm

        Mat original_w_img_877;       //877.940nm
        Mat original_w_img_886;       //886.689nm
        Mat original_w_img_869;       //869.256nm
        Mat original_w_img_858;       //858.490nm
        Mat original_w_img_944;       //944.466nm
        Mat original_w_img_783;       //783.508nm
        Mat original_w_img_796;       //796.428nm
        Mat original_w_img_772;       //772.240nm
        Mat original_w_img_758;       //758.962nm
        Mat original_w_img_665;       //665.883nm
        Mat original_w_img_732;       //732.043nm
        Mat original_w_img_746;       //746.304nm
        Mat original_w_img_720;       //720.119nm
        Mat original_w_img_705;       //705.457nm
        Mat original_w_img_680;       //680.543nm
        Mat original_w_img_919;       //919.833nm
        Mat original_w_img_926;       //926.032nm
        Mat original_w_img_910;       //910.186nm
        Mat original_w_img_902;       //902.089nm
        Mat original_w_img_939;       //939.834nm
        Mat original_w_img_837;       //837.423nm
        Mat original_w_img_848;       //848.456nm
        Mat original_w_img_827;       //827.127nm
        Mat original_w_img_815;       //815.456nm
        Mat original_w_img_934;       //934.769nm

        Mat calibration_img_877;       //877.940nm
        Mat calibration_img_886;       //886.689nm
        Mat calibration_img_869;       //869.256nm
        Mat calibration_img_858;       //858.490nm
        Mat calibration_img_944;       //944.466nm
        Mat calibration_img_783;       //783.508nm
        Mat calibration_img_796;       //796.428nm
        Mat calibration_img_772;       //772.240nm
        Mat calibration_img_758;       //758.962nm
        Mat calibration_img_665;       //665.883nm
        Mat calibration_img_732;       //732.043nm
        Mat calibration_img_746;       //746.304nm
        Mat calibration_img_720;       //720.119nm
        Mat calibration_img_705;       //705.457nm
        Mat calibration_img_680;       //680.543nm
        Mat calibration_img_919;       //919.833nm
        Mat calibration_img_926;       //926.032nm
        Mat calibration_img_910;       //910.186nm
        Mat calibration_img_902;       //902.089nm
        Mat calibration_img_939;       //939.834nm
        Mat calibration_img_837;       //837.423nm
        Mat calibration_img_848;       //848.456nm
        Mat calibration_img_827;       //827.127nm
        Mat calibration_img_815;       //815.456nm
        Mat calibration_img_934;       //934.769nm

        float first_image_0_sum[4];
        float first_image_1_sum[4];
        float first_image_2_sum[4];
        float first_image_3_sum[4];
        float first_image_4_sum[4];
        float first_image_5_sum[4];
        float first_image_6_sum[4];
        float first_image_7_sum[4];
        float first_image_8_sum[4];
        float first_image_9_sum[4];
        float first_image_10_sum[4];
        float first_image_11_sum[4];
        float first_image_12_sum[4];
        float first_image_13_sum[4];
        float first_image_14_sum[4];
        float first_image_15_sum[4];
        float first_image_16_sum[4];
        float first_image_17_sum[4];
        float first_image_18_sum[4];
        float first_image_19_sum[4];
        float first_image_20_sum[4];
        float first_image_21_sum[4];
        float first_image_22_sum[4];
        float first_image_23_sum[4];
        float first_image_24_sum[4];

        //白板标称值灰度值存储数组
        float first_0_sum[4];
        float first_1_sum[4];
        float first_2_sum[4];
        float first_3_sum[4];
        float first_4_sum[4];
        float first_5_sum[4];
        float first_6_sum[4];
        float first_7_sum[4];
        float first_8_sum[4];
        float first_9_sum[4];
        float first_10_sum[4];
        float first_11_sum[4];
        float first_12_sum[4];
        float first_13_sum[4];
        float first_14_sum[4];
        float first_15_sum[4];
        float first_16_sum[4];
        float first_17_sum[4];
        float first_18_sum[4];
        float first_19_sum[4];
        float first_20_sum[4];
        float first_21_sum[4];
        float first_22_sum[4];
        float first_23_sum[4];
        float first_24_sum[4];
    };
}

#endif //HYPERSPECTRALIMAGE_H
