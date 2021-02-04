#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("../test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	char INPUT_WIN[] = "input image";
	char OUTPUT_WIN[] = "Border Demo";
	namedWindow(INPUT_WIN, WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_WIN, WINDOW_AUTOSIZE);
	imshow(INPUT_WIN, src);
	/*
	int top = (int)(0.05*src.rows);
	int bottom = (int)(0.05*src.rows);
	int left = (int)(0.05*src.cols);
	int right = (int)(0.05*src.cols);
	RNG rng(12345);
	int borderType = BORDER_DEFAULT;

	int c = 0;
	while (true) {
		c = waitKey(500);
		// ESC
		if ((char)c == 27) {
			break;
		}
		if ((char)c == 'r') {
			borderType = BORDER_REPLICATE;
		} else if((char)c == 'w') {
			borderType = BORDER_WRAP;
		} else if((char)c == 'c') {
			borderType = BORDER_CONSTANT;
		} 
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		copyMakeBorder(src, dst, top, bottom, left, right, borderType, color);
		imshow(OUTPUT_WIN, dst);
	}
	*/

	GaussianBlur(src, dst, Size(5, 5), 0, 0, BORDER_WRAP);
	imshow(OUTPUT_WIN, dst);

	waitKey(0);
	return 0;
}