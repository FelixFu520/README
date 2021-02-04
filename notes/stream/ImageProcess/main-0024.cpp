#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src = imread("../test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	char INPUT_T[] = "input image";
	char OUTPUT_T[] = "histogram demo";
	namedWindow(INPUT_T, WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_T, WINDOW_AUTOSIZE);
	imshow(INPUT_T, src);

    //分通道显示
	vector<Mat> bgr_planes;
	split(src, bgr_planes);
	imshow("single channel demo", bgr_planes[0]);

    //计算直方图
	int histSize = 256;
	float range[] = { 0, 256 };
	const float *histRanges = { range };
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRanges, true, false);

    //归一化
	int hist_h = 400;
	int hist_w = 512;
	int bin_w = hist_w / histSize;
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
	normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());

	// render histogram chart
	for (int i = 1; i < histSize; i++) {
		line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))), 
			Point((i)*bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, LINE_AA);

		line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, LINE_AA);

		line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow(OUTPUT_T, histImage);

	waitKey(0);
	return 0;
}
