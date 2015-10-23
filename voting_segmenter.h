#ifndef __VOTING_SEGMENTER_H__
#define __VOTING_SEGMENTER_H__

#include "pfsegmenter.h"
#include "background_subtracter.h"
#include "grid_seams.h"

#include <opencv2/opencv.hpp>

enum class VSMethod {THRESHOLD};

class VotingSegmenter : public PFSegmenter {

private:

	BackgroundSubtracter* pBS;

	VSMethod vsMethod = VSMethod::THRESHOLD;
	BSMethod bsMethod = BSMethod::MOG;

	GridSeams gs;

	// params
	double thresh = 0.5;

	void init();

public:

	VotingSegmenter();

	VotingSegmenter(BSMethod bsMethod);

	VotingSegmenter(VSMethod vsMethod, BSMethod bsMethod=BSMethod::MOG);

	void parse(cv::Mat& frame, cv::Mat& segMask);

	// getters and setters
	double getThreshold();
	void setThreshold(double thresh);

};

#endif
