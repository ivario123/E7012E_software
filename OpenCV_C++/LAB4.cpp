#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

static int green();
static int red();
static int startStop(int LowH, int HighH, int LowS, int HighS, int LowV, int HighV);

int main(int argc, char** argv) {

	green();
}

static int green() {
	int iLowH = 56;
	int iHighH = 88;

	int iLowS = 75;
	int iHighS = 255;

	int iLowV = 78;
	int iHighV = 255;	//Sets the hue values to only detect green

	int i = startStop(iLowH, iHighH, iLowS, iHighS, iLowV, iHighV); //start the loop with the Hue values
	if (i == 1) {
		cout << "Start" << endl;	//replace with start engine
		return red();	//if successfull start search for red
	}
}

static int red() {
	int iLowH = 0;
	int iHighH = 10;

	int iLowS = 100;
	int iHighS = 255;

	int iLowV = 100;
	int iHighV = 255;	//Sets the hue values to only detect red

	int i = startStop(iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
	if (i == 1) {
		cout << "Stop" << endl;	//replace with stop the engine
	}
	return -1;
}

static int startStop(int LowH, int HighH, int LowS, int HighS, int LowV, int HighV) {
	VideoCapture cap(0);
	/*	if (cap.isOpened() == false) {
			cout << "no video camera" << endl;
			cin.get();
			return -1;
		}*/

	while (true) {
		Mat imgOriginal, imgHSV, imgThreshold; //array to store picture data

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video
		/*		if (!bSuccess) //if not success, break loop
				{
					cout << "Cannot read a frame from video stream" << endl;
					break;
				}
		*/
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);	//color converter

		inRange(imgHSV, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), imgThreshold); //Filter out colors

		GaussianBlur(imgThreshold, imgThreshold, Size(9, 9), 2, 2);	//Doesn't work without

		vector<Vec3f> circles;
		HoughCircles(imgThreshold, circles, HOUGH_GRADIENT, 2, imgThreshold.rows / 4, 200, 100); //detect the circle

		if (!circles.empty()) {
			return 1;
			break; //break the loop if a circle is detected
		}

		imshow("image", imgThreshold);
		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

}