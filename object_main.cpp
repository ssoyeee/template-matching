#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\core.hpp"
#include "opencv2\objdetect.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

//전역변수선언
Mat img; 
Mat templ; 
Mat result;
String image_window = "Source Image";
String result_window = "Result window";

int match_method;
int max_Trackbar = 5;

//함수의 헤더 부분
void MatchingMethod(int, void*);

int main(int, char** argv)
		{
			Mat img, templ, result;
			double minVal, maxVal;
			Point minLoc, maxLoc, matchLoc;

			img = imread("Bananatree.jpg", 0);
			templ = imread("Banana.jpg", 0);


			Mat img_display;
			img.copyTo(img_display);

			int result_cols = img.cols - templ.cols + 1;
			int result_rows = img.rows - templ.rows + 1;
			result.create(result_rows, result_cols, CV_32FC1);
			matchTemplate(img, templ, result, TM_CCOEFF_NORMED);
			normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

			minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

			matchLoc = maxLoc;
			rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(255), 2, 8, 0);

			imshow("Source Image", img_display);
			imshow("template Image", templ);

			waitKey(0);
			return 0;
		}



void MatchingMethod(int, void*)
{
	//보여줄 source 이미지
	Mat img_display;
	img.copyTo(img_display);
	//결과 이미지 행렬 만들기
	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;

	result.create(result_cols, result_rows, CV_32FC1);

	//템플릿과 매칭, normalize
	matchTemplate(img, templ, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());


	Point minLoc; Point maxLoc;
	Point matchLoc;
	double minVal; double maxVal;

	for (int k = 1; k <= 5; k++)
	{
		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());


		if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
		{
			result.at<float>(minLoc.x, minLoc.y) = 1.0;
			result.at<float>(maxLoc.x, maxLoc.y) = 1.0;
		}
		else
		{
			result.at<float>(minLoc.x, minLoc.y) = 0.0;
			result.at<float>(maxLoc.x, maxLoc.y) = 0.0;
		}

	
		if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
		{
			matchLoc = minLoc;
		}
	}
}