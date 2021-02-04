#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("../test.jpg");
	if (!src.data) {
		printf("could not load image");
	}
	char input_title[] = "input image";
	char output_title[] = "Laplaiance Result";
	namedWindow(input_title, WINDOW_AUTOSIZE);
	imshow(input_title, src);

	Mat gray_src, edge_image;
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, gray_src, COLOR_BGR2GRAY);

	Laplacian(gray_src, edge_image, CV_16S, 3);
	convertScaleAbs(edge_image, edge_image);

	threshold(edge_image, edge_image, 0, 255, THRESH_OTSU | THRESH_BINARY);
	namedWindow(output_title, WINDOW_AUTOSIZE);
	imshow(output_title, edge_image);

	waitKey(0);
	return 0;
}