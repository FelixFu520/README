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

	cvtColor(src, src, COLOR_BGR2GRAY);
	equalizeHist(src, dst);
	char INPUT_T[] = "input image";
	char OUTPUT_T[] = "result image";
	namedWindow(INPUT_T, WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_T, WINDOW_AUTOSIZE);

	imshow(INPUT_T, src);
	imshow(OUTPUT_T, dst);

	waitKey(0);
	return 0;
}