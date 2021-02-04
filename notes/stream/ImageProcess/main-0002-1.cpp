#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
using namespace cv;
int main(int argc, char** argv)
{
	Mat testImage = imread("../test.jpg");
	CV_Assert(testImage.depth() == CV_8U);
	namedWindow("test_image", WINDOW_NORMAL);
	imshow("test_image", testImage);

	Mat result;
	Mat kern = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(testImage, result, testImage.depth(), kern);

	namedWindow("result_image", WINDOW_NORMAL);
	imshow("result_image", result);
	waitKey(0);
	return 0;
}
