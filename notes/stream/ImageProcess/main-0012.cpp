#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("../t2.png");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}

	char INPUT_WIN[] = "input image";
	char OUTPUT_WIN[] = "result image";
	namedWindow(INPUT_WIN, WINDOW_AUTOSIZE);
	imshow(INPUT_WIN, src);

	Mat gray_src;
	cvtColor(src, gray_src, COLOR_BGR2GRAY);
	imshow("gray image", gray_src);
	
	Mat binImg;
	adaptiveThreshold(~gray_src, binImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	imshow("binary image", binImg);

    //水平结构元素
	Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1), Point(-1, -1));
    //垂直结构元素
	Mat vline = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16), Point(-1, -1));
    //矩形结构
	Mat kernel = getStructuringElement(MORPH_RECT, Size(4, 4), Point(-1, -1));

	Mat temp;
    /*提取水平/垂直线 t1.png
    erode(binImg, temp, vline);
    dilate(temp, dst, vline);
    */
    
    /*提取水平/垂直线 等同erode + dilate 
    morphologyEx(binImg, dst, MORPH_OPEN, vline);
    */
    
	erode(binImg, temp, kernel);
	dilate(temp, dst, kernel);

	
	bitwise_not(dst, dst); 
	//blur(dst, dst, Size(3, 3), Point(-1, -1)); //模糊A字母(提取水平线)
	imshow("Final Result", dst);

	waitKey(0);
	return 0;
}
