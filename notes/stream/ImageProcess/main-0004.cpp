#include<opencv2/opencv.hpp>
#include <iostream>
// #include <opencv2/core/core.hpp> 
// #include <opencv2/imgcodecs.hpp> 
// #include <opencv2/opencv.hpp>
// #include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv){
    cv::Mat src;
    src = cv::imread("../test.jpg");
    if(src.empty()){
        std::cout<< "could not load image ..."<<std::endl;
        return -1;
    }
    
    cv::namedWindow("input", cv::WINDOW_AUTOSIZE);
    cv::imshow("input", src);
    
    cv::Mat gray_src;
    cv::cvtColor(src, gray_src, cv::COLOR_BGR2GRAY);
    cv::namedWindow("input gray", cv::WINDOW_AUTOSIZE);
    cv::imshow("input gray", gray_src);
    
    
    cv::Mat dst;
    dst.create(src.size(), src.type());
    int height = src.rows;
    int width = src.cols;
    int nc = src.channels();
    /*
    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){
            if(nc==1){
                int gray = gray_src.at<uchar>(row,col);
                gray_src.at<uchar>(row,col) = 255 - gray;
            }else if(nc==3){
                int b = src.at<cv::Vec3b>(row,col)[0];
                int g = src.at<cv::Vec3b>(row,col)[1];
                int r = src.at<cv::Vec3b>(row,col)[2];
                dst.at<cv::Vec3b>(row,col)[0]=0;
                dst.at<cv::Vec3b>(row,col)[1]=g;
                dst.at<cv::Vec3b>(row,col)[2]=r;  
                //gray_src.at<uchar>(row,col)=max(b,min(g,r));
            }
        }
    }
    */
    cv::bitwise_not(src,dst);
    cv::imshow("output", dst);
    cv::waitKey(0);
    return 0;
}

