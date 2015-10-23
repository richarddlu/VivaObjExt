#ifndef __MOG2_BACKGROUND_SUBTRACTER_H__
#define __MOG2_BACKGROUND_SUBTRACTER_H__

#include "background_subtracter.h"

#include <opencv2/opencv.hpp>

class MOG2BackgroundSubtracter : public BackgroundSubtracter {

private:

	cv::Ptr<cv::BackgroundSubtractor> pBS;

public:

	MOG2BackgroundSubtracter();

	void parse(cv::Mat& frame, cv::Mat& binaryMask);

};

#endif
