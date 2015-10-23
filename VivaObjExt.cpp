#include "voting_segmenter.h"

#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	VideoCapture cap("inputs/bird_of_paradise.avi");
	if(!cap.isOpened()){
		cout<<"cannot open file."<<endl;
		return -1;
	}else
		cout<<"open file successfully."<<endl;

	// This does not actually resize the frames. Not necessary. It seems they only effect the get method of VideoCapture?
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 360);

	double fps = cap.get(CV_CAP_PROP_FPS);

	namedWindow("video", CV_WINDOW_AUTOSIZE);
	namedWindow("mask", CV_WINDOW_AUTOSIZE);

	// creating segmenter
	PFSegmenter* segmenter = new VotingSegmenter(BSMethod::MOG2);

	while(1){
		Mat frame;

		bool bSuccess = cap.read(frame);

		if(!bSuccess){
			cout<<"cannot read frame."<<endl;
			break;
		}

		resize(frame, frame, Size(640,360));	// Here we actually resize the frame
												// For the interpolation options, see http://docs.opencv.org/modules/imgproc/doc/geometric_transformations.html#resize

		// segmentation
		Mat segMask;
		segmenter->parse(frame, segMask);

		imshow("video", frame);
		imshow("mask", segMask);

		// if(waitKey(1000/(int)fps) == 27){
		if(waitKey(1) ==  27) {
			cout<<"close"<<endl;
			break;
		}
	}

	return 0;
}
