#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>


int main(int argc, char** argv) {
	cv::Mat src;
	src = cv::imread("../test.jpg");
	if (src.empty()) {
		std::cout << "could not load image..." << std::endl;
		return -1;
	}
	cv::namedWindow("input", cv::WINDOW_NORMAL);
	cv::imshow("input", src);

    /*
	cv::Mat dst;
	dst = cv::Mat(src.size(), src.type());
	dst = cv::Scalar(127, 0, 255);
	cv::namedWindow("output", cv::WINDOW_AUTOSIZE);
	cv::imshow("output", dst);
    */
    
    /*
	cv::Mat dst;
	src.copyTo(dst);
	cv::namedWindow("output", cv::WINDOW_NORMAL);
    cv::imshow("output", dst);
    */

    /*
    cv::Mat dst;
	cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
	printf("input image channels : %d\n", src.channels());
	printf("output image channels : %d\n", dst.channels());

	int cols = dst.cols;
	int rows = dst.rows;

	printf("rows : %d cols : %d\n", rows, cols);
	const uchar* firstRow = dst.ptr<uchar>(0);
	printf("fist pixel value : %d\n", *firstRow);
    */
    
    /*
	cv::Mat M(100, 100, CV_8UC1, cv::Scalar(127));
	std::cout << "M =" << std::endl << M << std::endl;
    */
    
	cv::Mat m1;
	m1.create(src.size(), src.type());
	m1 = cv::Scalar(0, 0, 255);

	cv::Mat csrc;
	cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cv::filter2D(src, csrc, -1, kernel);

	cv::Mat m2 = cv::Mat::eye(2, 2, CV_8UC1);
	std::cout << "m2 =" << std::endl << m2 << std::endl;

	cv::imshow("output", m2);
	cv::waitKey(0);
	return 0;
}