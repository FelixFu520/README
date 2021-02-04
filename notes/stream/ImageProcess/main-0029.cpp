#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;
Mat src, src_gray, dst;
int threshold_value = 100;
int threshold_max = 255;
const char* output_win = "convex hull demo";
void Threshold_Callback(int, void*);
RNG rng(12345);
int main(int argc, char** argv) {
	src = imread("../test.png");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	const char* input_win = "input image";
	namedWindow(input_win, WINDOW_AUTOSIZE);
	namedWindow(output_win, WINDOW_NORMAL);
	const char* trackbar_label = "Threshold : ";

	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);
	imshow(input_win, src_gray);

	createTrackbar(trackbar_label, output_win, &threshold_value, threshold_max, Threshold_Callback);
	Threshold_Callback(0, 0);
	waitKey(0);
	return 0;
}

void Threshold_Callback(int, void*) {
	Mat bin_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	
	threshold(src_gray, bin_output, threshold_value, threshold_max, THRESH_BINARY);
	findContours(bin_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>> convexs(contours.size());
	for (size_t i = 0; i < contours.size(); i++) {
		convexHull(contours[i], convexs[i], false, true);
	}

	dst = Mat::zeros(src.size(), CV_8UC3);
	vector<Vec4i> empty(0);
	for (size_t k = 0; k < contours.size(); k++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, k, color, 2, LINE_8, hierachy, 0, Point(0, 0));
		drawContours(dst, convexs, k, color, 2, LINE_8, empty, 0, Point(0, 0));
	}
	imshow(output_win, dst);

	return;
}
