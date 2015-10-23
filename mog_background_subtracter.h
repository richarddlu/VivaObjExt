#ifndef __MOG_BACKGROUND_SUBTRACTER_H__
#define __MOG_BACKGROUND_SUBTRACTER_H__

#include "background_subtracter.h"

#include <opencv2/opencv.hpp>

class MOGBackgroundSubtracter : public BackgroundSubtracter {

private:

	cv::Ptr<cv::BackgroundSubtractor> pBS;

public:

	MOGBackgroundSubtracter();

	void parse(cv::Mat& frame, cv::Mat& binaryMask);

};

#endif
