#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
static const char WINTITLE[] = "randomlines-demo";

int drawRandomLines(Mat image) {
	RNG rng(0xffffff);
	Point pt1, pt2;
	for (int i = 0; i < 100000; i++) {
		pt1.x = rng.uniform(0, image.cols);
		pt2.x = rng.uniform(0, image.cols);
		pt1.y = rng.uniform(0, image.rows);
		pt2.y = rng.uniform(0, image.rows);
		int r = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int b = rng.uniform(0, 255);
		line(image, pt1, pt2, Scalar(b, g, r), 1, LINE_8);
		putText(image, "Open CV Core Tutorial", Point(image.cols / 2-200, image.rows / 2), 
			FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 255, 0), 3, LINE_8);

		imshow(WINTITLE, image);
		if (waitKey(10) >= 0)
		{ 
			return -1; 
		}
	}
	return 0;
}

int main(int argc, char** argv) {
	Mat image = Mat::zeros(Size(450, 450), CV_8UC3);
	namedWindow(WINTITLE, WINDOW_AUTOSIZE);
	int ok = drawRandomLines(image);
	if (ok != 0) {
		return 0;
	}
	return 0;
}