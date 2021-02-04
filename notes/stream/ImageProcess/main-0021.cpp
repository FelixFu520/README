#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("../c.png");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	char INPUT_TITLE[] = "input image";
	char OUTPUT_TITLE[] = "hough circle demo";
	namedWindow(INPUT_TITLE, WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_TITLE, WINDOW_AUTOSIZE);
	imshow(INPUT_TITLE, src);

    //中值滤波
	Mat moutput;
	medianBlur(src, moutput, 3);
	cvtColor(moutput, moutput, COLOR_BGR2GRAY);

    //霍夫圆检测
	vector<Vec3f> pcircles;
	HoughCircles(moutput, pcircles, HOUGH_GRADIENT, 1, 10, 100, 30, 5, 50);
	src.copyTo(dst);
	for (size_t i = 0; i < pcircles.size(); i++) {
		Vec3f cc = pcircles[i];
		circle(dst, Point(cc[0], cc[1]), cc[2], Scalar(0, 0, 255), 2, LINE_AA);
		circle(dst, Point(cc[0], cc[1]), 2, Scalar(198, 23, 155), 2, LINE_AA);
	}
	imshow(OUTPUT_TITLE, dst);

	waitKey(0);
	return 0;
}
