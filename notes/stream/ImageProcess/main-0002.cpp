#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>


int main(int argc, char** argv) {
	cv::Mat src, dst;
	src = cv::imread("../test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	cv::namedWindow("input image", cv::WINDOW_AUTOSIZE);
	cv::imshow("input image", src);
	
	
	int cols = (src.cols-1) * src.channels();
	int offsetx = src.channels();
	int rows = src.rows;
    /*
	dst = cv::Mat::zeros(src.size(), src.type());
	for (int row = 1; row < (rows - 1); row++) {
		const uchar* previous = src.ptr<uchar>(row - 1);
		const uchar* current = src.ptr<uchar>(row);
		const uchar* next = src.ptr<uchar>(row + 1);
		uchar* output = dst.ptr<uchar>(row);
		for (int col = offsetx; col < cols; col++) {
			output[col] = cv::saturate_cast<uchar>(5 * current[col] - (current[col- offsetx] + current[col+ offsetx] + previous[col] + next[col]));
		}
	}
	*/
	double t = cv::getTickCount();
	cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(src, dst, src.depth(), kernel);
	double timeconsume = (cv::getTickCount() - t) / cv::getTickFrequency();
	printf("tim consume %.2f\n", timeconsume);

	cv::namedWindow("contrast image demo", cv::WINDOW_AUTOSIZE);
	cv::imshow("contrast image demo", dst);

	cv::waitKey(0);
	return 0;
}

