#ifndef __PFSEGMENTER_H__
#define __PFSEGMENTER_H__

#include "segmenter.h"

#include <opencv2/opencv.hpp>

/**
 * Per-frame segmenter
 */
class PFSegmenter : public Segmenter {

public:

	virtual void parse(cv::Mat& frame, cv::Mat& segMask) = 0;

};

#endif
