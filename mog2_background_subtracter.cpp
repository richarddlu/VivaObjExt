#include "mog2_background_subtracter.h"

#include <opencv2/opencv.hpp>

MOG2BackgroundSubtracter::MOG2BackgroundSubtracter() {
	pBS = new cv::BackgroundSubtractorMOG2();
}

void MOG2BackgroundSubtracter::parse(cv::Mat& frame, cv::Mat& binaryMask) {
	pBS->operator()(frame, binaryMask, 1.0/100);
}
