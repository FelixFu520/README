#include <opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char** argv) {
	cv::Mat src1, src2, dst;
	src1 = cv::imread("../linux.jpg");
	src2 = cv::imread("../win.jpg");
	if (!src1.data) {
		std::cout << "could not load image Linux Logo..." << std::endl;
		return -1;
	}
	if (!src2.data) {
		std::cout << "could not load image WIN7 Logo..." << std::endl;
		return -1;
	}

	double alpha = 0.5;
	if (src1.rows == src2.rows && src1.cols == src2.cols && src1.type() == src2.type()) {
// 		cv::addWeighted(src1, alpha, src2, (1.0 - alpha), 0.0, dst);
		cv::multiply(src1, src2, dst, 1.0);
		
		cv::imshow("linuxlogo", src1);
		cv::imshow("win7logo", src2);
		cv::namedWindow("blend demo", cv::WINDOW_AUTOSIZE);
		cv::imshow("blend demo", dst);
	}
	else {
		printf("could not blend images , the size of images is not same...\n");
		return -1;
	}

	cv::waitKey(0);
	return 0;
}