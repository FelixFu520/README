#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
// #include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>

// using namespace cv;

int main(int argc, char** argv){
    # read image
    cv::Mat src = cv::imread("../test.jpg");
    
    if(src.empty()){
        std::cout<< "load fail !"<<std::endl;
        return -1;
    }
    
    # show image
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::imshow("image", src);
    
    # change image
    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    cv::namedWindow("dst", cv::WINDOW_AUTOSIZE);
    cv::imshow("dst", dst);
    
    # write image
    cv::imwrite("../test.png", dst);
    
    cv::waitKey(0);
    return 0;
}