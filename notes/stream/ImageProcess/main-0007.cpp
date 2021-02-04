#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat bgImage;
const char* drawdemo_win = "draw shapes and text demo";
void MyLines();
void MyRectangle();
void MyEllipse();
void MyCircle();
void MyPolygon();
void RandomLineDemo();
int main(int argc, char** argv) {
	bgImage = cv::imread("../test.jpg");
	if (!bgImage.data) {
		printf("could not load image...\n");
		return -1;
	}
// 	MyLines();
// 	MyRectangle();
// 	MyEllipse();
// 	MyCircle();
// 	MyPolygon();

// 	cv::putText(bgImage, "Hello OpenCV", cv::Point(300, 300), cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(12, 23, 200), 1, 2);
// 	cv::namedWindow(drawdemo_win, cv::WINDOW_AUTOSIZE);
// 	cv::imshow(drawdemo_win, bgImage);

	RandomLineDemo();
	cv::waitKey(0);
	return 0;
}

void MyLines() {
	cv::Point p1 = cv::Point(20, 30);
	cv::Point p2;
	p2.x = 400;
	p2.y = 400;
	cv::Scalar color = cv::Scalar(0, 0, 255);
	cv::line(bgImage, p1, p2, color, 1, cv::LINE_AA);
}

void MyRectangle() {
	cv::Rect rect = cv::Rect(200, 100, 300, 300);
	cv::Scalar color = cv::Scalar(255, 0, 0);
	cv::rectangle(bgImage, rect, color, 2, cv::LINE_8);
}

void MyEllipse() {
	cv::Scalar color = cv::Scalar(0, 255, 0);
	cv::ellipse(bgImage, cv::Point(bgImage.cols / 2, bgImage.rows / 2), cv::Size(bgImage.cols / 4, bgImage.rows / 8), 90, 0, 360, color, 2, cv::LINE_8);
}

void MyCircle() {
	cv::Scalar color = cv::Scalar(0, 255, 255);
	cv::Point center = cv::Point(bgImage.cols / 2, bgImage.rows / 2);
	cv::circle(bgImage, center, 150, color, 2, 8);
}

void MyPolygon() {
	cv::Point pts[1][5];
	pts[0][0] = cv::Point(100, 100);
	pts[0][1] = cv::Point(100, 200);
	pts[0][2] = cv::Point(200, 200);
	pts[0][3] = cv::Point(200, 100);
	pts[0][4] = cv::Point(100, 100);

	const cv::Point* ppts[] = { pts[0] };
	int npt[] = { 5 };
	cv::Scalar color = cv::Scalar(255, 12, 255);

	cv::fillPoly(bgImage, ppts, npt, 1, color, 8);
}

void RandomLineDemo() {
	cv::RNG rng(12345);
	cv::Point pt1;
	cv::Point pt2;
	cv::Mat bg = cv::Mat::zeros(bgImage.size(), bgImage.type());
	cv::namedWindow("random line demo", cv::WINDOW_AUTOSIZE);
	for (int i = 0; i < 100; i++) {
		pt1.x = rng.uniform(0, bgImage.cols);
		pt2.x = rng.uniform(0, bgImage.cols);
		pt1.y = rng.uniform(0, bgImage.rows);
		pt2.y = rng.uniform(0, bgImage.rows);
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		if (cv::waitKey(50) > 0) {
			break;
		}
		cv::line(bg, pt1, pt2, color, 1, 8);
		cv::imshow("random line demo", bg);
	}
}


