#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
int main(int argc, char** argv) {
	cv::Mat src, dst;
	src = cv::imread("../test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
    
	char input_win[] = "input image";
// 	cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
	cv::namedWindow(input_win, cv::WINDOW_AUTOSIZE);
	cv::imshow(input_win, src);

	// contrast and brigthtness changes 
	int height = src.rows;
	int width = src.cols;
	dst = cv::Mat::zeros(src.size(), src.type());
	float alpha = 1.2;
	float beta = 30;

	cv::Mat m1;
	src.convertTo(m1, CV_32F); //和Vec3f对应
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (src.channels() == 3) {
				float b = m1.at<cv::Vec3f>(row, col)[0];// blue
				float g = m1.at<cv::Vec3f>(row, col)[1]; // green
				float r = m1.at<cv::Vec3f>(row, col)[2]; // red

				// output
				dst.at<cv::Vec3b>(row, col)[0] = cv::saturate_cast<uchar>(b*alpha + beta);
				dst.at<cv::Vec3b>(row, col)[1] = cv::saturate_cast<uchar>(g*alpha + beta);
				dst.at<cv::Vec3b>(row, col)[2] = cv::saturate_cast<uchar>(r*alpha + beta);
			}
			else if (src.channels() == 1) {
				float v = src.at<uchar>(row, col);
				dst.at<uchar>(row, col) = cv::saturate_cast<uchar>(v*alpha + beta);
			}
		}
	}

	char output_title[] = "contrast and brightness change demo";
	cv::namedWindow(output_title, cv::WINDOW_AUTOSIZE);
	cv::imshow(output_title, dst);

	cv::waitKey(0);
	return 0;
}