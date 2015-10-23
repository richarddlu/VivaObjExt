#include "mog_background_subtracter.h"

#include <opencv2/opencv.hpp>

MOGBackgroundSubtracter::MOGBackgroundSubtracter() {
	pBS = new cv::BackgroundSubtractorMOG();
}

void MOGBackgroundSubtracter::parse(cv::Mat& frame, cv::Mat& binaryMask) {
	pBS->operator()(frame, binaryMask, 1.0/100);
}
