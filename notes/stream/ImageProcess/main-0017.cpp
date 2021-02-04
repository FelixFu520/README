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

	char INPUT_TITLE[] = "input image";
	char OUTPUT_TITLE[] = "sobel-demo";
	namedWindow(INPUT_TITLE, WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_TITLE, WINDOW_AUTOSIZE);
	imshow(INPUT_TITLE, src);

    //1.高斯平滑
	Mat gray_src;
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
    //2.转灰度
	cvtColor(dst, gray_src, COLOR_BGR2GRAY);
	imshow("gray image", gray_src);

    //3.求梯度
	Mat xgrad, ygrad;
	Scharr(gray_src, xgrad, CV_16S, 1, 0);
	Scharr(gray_src, ygrad, CV_16S, 0, 1);
// 	Sobel(gray_src, xgrad, CV_16S, 1, 0, 3);
// 	Sobel(gray_src, ygrad, CV_16S, 0, 1, 3);
    
	convertScaleAbs(xgrad, xgrad);
	convertScaleAbs(ygrad, ygrad);
	imshow("xgrad", xgrad);
	imshow("ygrad", ygrad);

	Mat xygrad = Mat(xgrad.size(), xgrad.type());
	printf("type : %d\n", xgrad.type());
	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);
		}
	}
	addWeighted(xgrad, 0.5, ygrad, 0.5, 0, xygrad);
	imshow(OUTPUT_TITLE, xygrad);

	waitKey(0);
	return 0;
}