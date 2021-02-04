#include <opencv2/opencv.hpp> 
#include <iostream> 
// using namespace cv;

cv::Mat src, dst;
char OUTPUT_WIN[] = "output image";
int element_size = 3;
int max_size = 21;
void CallBack_Demo(int, void*);
int main(int argc, char** argv) {
	
	src = cv::imread("../test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	cv::namedWindow("input image", cv::WINDOW_AUTOSIZE);
	cv::imshow("input image", src);

	cv::namedWindow(OUTPUT_WIN, cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("Element Size :", OUTPUT_WIN, &element_size, max_size, CallBack_Demo);
	CallBack_Demo(0, 0);

	cv::waitKey(0);
	return 0;
}

void CallBack_Demo(int, void*) {
	int s = element_size * 2 + 1;
	cv::Mat structureElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(s, s), cv::Point(-1, -1));
	dilate(src, dst, structureElement, cv::Point(-1, -1), 1);
// 	cv::erode(src, dst, structureElement);
	cv::imshow(OUTPUT_WIN, dst);
	return;
}
