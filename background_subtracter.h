#ifndef __BACKGROUND_SUBTRACTER_H__
#define __BACKGROUND_SUBTRACTER_H__

#include <opencv2/opencv.hpp>

enum class BSMethod {MOG, MOG2};

class BackgroundSubtracter {

public:

	virtual void parse(cv::Mat& frame, cv::Mat& binaryMask) = 0;

};

#endif
