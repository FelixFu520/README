#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("../test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
	}
	namedWindow("input image", WINDOW_AUTOSIZE);
	imshow("input image", src);
	char output_title[] = "morphology demo";
	namedWindow(output_title, WINDOW_AUTOSIZE);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11), Point(-1, -1));
	morphologyEx(src, dst, MORPH_BLACKHAT, kernel);//CV_MOP_BLACKHAT
	imshow(output_title, dst);

	waitKey(0);
	return 0;
}
/*
MORPH_ERODE	0	图像腐蚀
MORPH_DILATE	1	图像膨胀
MORPH_OPEN	2	开运算
MORPH_CLOSE	3	闭运算
MORPH_GRADIENT	4	形态学梯度
MORPH_TOPHAT	5	顶帽运算
MORPH_BLACKHAT	6	黑帽运算
MORPH_HITMISS	7	击中击不中运算
*/