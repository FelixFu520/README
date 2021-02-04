#include <opencv2/core/core.hpp> 
#include <opencv2/imgcodecs.hpp> 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main(int argc, char** args) {
	Mat image = imread("D:/test.jpg", IMREAD_COLOR);
	if (image.empty()) {
		cout << "could not find the image resource..." << std::endl;
		return -1;
	}

	Mat grayImg;
	cvtColor(image, grayImg, COLOR_BGR2GRAY);
	Mat sobelx; 
	Sobel(grayImg, sobelx, CV_32F, 1, 0);
	double minVal, maxVal;
	minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
	Mat draw;
	sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
	/*
	int height = image.rows;
	int width = image.cols;
	int channels = image.channels();
	printf("height=%d width=%d channels=%d", height, width, channels);
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (channels == 3) {
				image.at<Vec3b>(row, col)[0] = 0; // blue
				image.at<Vec3b>(row, col)[1] = 0; // green
			}
		}
	}
	*/
	namedWindow("My Image", CV_WINDOW_AUTOSIZE);
	imshow("My Image", draw);
	waitKey(0);
	return 0;
}