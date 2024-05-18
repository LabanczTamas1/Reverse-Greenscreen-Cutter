// C++ program for the above approach 
#include <iostream> 
#include <opencv2/opencv.hpp> 
#include "histo.h"

using namespace cv;
using namespace std;

void eloterMasolo(const Mat fg, Mat& bg) {
	// BGR képpont létrehozása
	Vec3b c;
	// átméretezés
	resize(bg, bg, fg.size());
	// sor oszlop ciklus
	for (int i = 0; i < fg.rows; i++)
	{
		for (int j = 0; j < fg.cols; j++) {
			// képpont c változóba mentése
			c = fg.at<Vec3b>(i, j);
			// ha nem fehér a képpont nem másolja át a háttérre
			if (c[0] < 200 || c[1] < 200 || c[2] < 200) {
				bg.at<Vec3b>(i, j) = c;
			}
		}
	}
}


// Driver code 
int main()
{

	Mat img = imread("p.jpg", IMREAD_COLOR), dest;

	dest = img.clone();
	medianBlur(img, img, 5);
	imshow("kezdeti", img);

	Mat imgc = img.clone();

	Mat hsv;
	cvtColor(img, hsv, COLOR_BGR2HSV);

	// A zöld színtartomány beállítása HSV színtérben
	Scalar lower_green(35, 20, 20); // Zöld alsó határ (HSV színtérben)
	Scalar upper_green(85, 255, 255); // Zöld felső határ (HSV színtérben)

	// Zöld színtartományon belüli maszk létrehozása
	Mat mask;
	inRange(hsv, lower_green, upper_green, mask);

	// Eredeti kép maszkolása a zöld színnel

	imgc.setTo(0, 255 - mask);
	imshow("Cloned Image", imgc);
	vector<Mat> chs;
	split(imgc, chs);

	chs[2] = 0;
	imshow("mask_e", imgc);
	merge(chs, imgc);
	imshow("1", imgc);

	img.setTo(255, mask);

	imshow("2", img);

	imgc.copyTo(img, mask);

	imshow("3", imgc);
	imshow("Original Image", img);





	waitKey(0);
	return 0;
}
