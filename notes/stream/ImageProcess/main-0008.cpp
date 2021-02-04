#include <opencv2/opencv.hpp> 
#include <iostream> 

int main(int argc, char** argv) {
	cv::Mat src, dst;
	src = cv::imread("../test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	char input_title[] = "input image";
	char output_title[] = "blur image";
	cv::namedWindow(input_title, cv::WINDOW_AUTOSIZE);
	cv::namedWindow(output_title, cv::WINDOW_AUTOSIZE);
	cv::imshow(input_title, src);

	cv::blur(src, dst, cv::Size(11, 11), cv::Point(-1, -1));
	imshow(output_title, dst);

	cv::Mat gblur;
	cv::GaussianBlur(src, gblur, cv::Size(11, 11), 11, 11);
	cv::imshow("gaussian blur", gblur);

	cv::waitKey(0);
	return 0;
}