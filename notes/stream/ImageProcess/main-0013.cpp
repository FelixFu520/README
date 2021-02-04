#include <opencv2/opencv.hpp>
#include <iostream>
#include "math.h"

using namespace cv;
int main(int agrc, char** argv) {
	Mat src, dst;
	src = imread("../test.jpg");
	if (!src.data) {
		printf("could not load image...");
		return -1;
	}

	char INPUT_WIN[] = "input image";
	char OUTPUT_WIN[] = "sample up";
	namedWindow(INPUT_WIN, WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_WIN, WINDOW_AUTOSIZE);
	imshow(INPUT_WIN, src);

    //上采样
	pyrUp(src, dst, Size(src.cols*2, src.rows * 2));
	imshow(OUTPUT_WIN, dst);

    //上采样
	Mat s_down;
	pyrDown(src, s_down, Size(src.cols / 2, src.rows / 2));
	imshow("sample down", s_down);

	// DOG
	Mat gray_src, g1, g2, dogImg;
	cvtColor(src, gray_src, COLOR_BGR2GRAY);
	GaussianBlur(gray_src, g1, Size(5, 5), 0, 0);
	GaussianBlur(g1, g2, Size(5, 5), 0, 0);
	subtract(g1, g2, dogImg, Mat());

    //归一化显示
	normalize(dogImg, dogImg, 255, 0, NORM_MINMAX);
	imshow("DOG Image", dogImg);

	waitKey(0);
	return 0;
}
