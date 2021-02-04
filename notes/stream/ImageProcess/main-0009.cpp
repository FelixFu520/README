#include <opencv2/opencv.hpp> 
#include <iostream> 
// using namespace cv;

int main(int argc, char** argv) {
	cv::Mat src, dst;
	src = cv::imread("../test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	cv::namedWindow("input image", cv::WINDOW_AUTOSIZE);
	cv::imshow("input image", src);

	//cv::medianBlur(src, dst, 3);
	cv::bilateralFilter(src, dst, 15, 100, 5);
	cv::namedWindow("BiBlur Filter Result", cv::WINDOW_AUTOSIZE);
	cv::imshow("BiBlur Filter Result", dst);

	cv::Mat resultImg;
	cv::Mat kernel = (cv::Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(dst, resultImg, -1, kernel, cv::Point(-1, -1), 0);
	cv::imshow("Final Result", resultImg);

    cv::Mat gblur;
    cv::GaussianBlur(src, gblur,cv::Size(15,15),3,3);
    cv::imshow("Gaussion Blur ", gblur);
	cv::waitKey(0);
	return 0;

}