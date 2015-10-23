#include "voting_segmenter.h"
#include "mog_background_subtracter.h"
#include "mog2_background_subtracter.h"
#include "grid_seams.h"

#include <opencv2/opencv.hpp>

using namespace cv;

VotingSegmenter::VotingSegmenter() {
	init();
}

VotingSegmenter::VotingSegmenter(BSMethod bsMethod) {
	this->bsMethod = bsMethod;
	init();
}

VotingSegmenter::VotingSegmenter(VSMethod vsMethod, BSMethod bsMethod) {
	this->vsMethod = vsMethod;
	this->bsMethod = bsMethod;
	init();
}

void VotingSegmenter::init() {
	switch(bsMethod) {
		case BSMethod::MOG:
			pBS = new MOGBackgroundSubtracter();
			break;
		case BSMethod::MOG2:
			pBS = new MOG2BackgroundSubtracter();
			break;
		default:
			pBS = new MOGBackgroundSubtracter();
	}
}

void VotingSegmenter::parse(cv::Mat& frame, cv::Mat& segMask) {
	cv::Mat bsResult;

	pBS->parse(frame, bsResult);
	switch(bsMethod) {
		case BSMethod::MOG2:
			threshold(bsResult, bsResult, 20, 255, THRESH_BINARY);
			break;
		default:
			break;
	}

	// calculating superpixels
	gs.process(frame, 15, 15, 0.5, 0.5);

	// counting superpixel sizes and votes
	int M = frame.size().width / 15;
    int N = frame.size().height / 15;
    int numClusters = (M+1) * (N+1);
        
    vector<int> labelCounts(numClusters);
    vector<int> voteCounts(numClusters);
    for(int i = 0; i < labelCounts.size(); i++)
        labelCounts[i] = 0;
    for(int h = 0; h < frame.rows; h++) {
        for(int w = 0; w < frame.cols; w++) {
            labelCounts[gs.labelMap.at<int>(h,w)]++;
            if(bsResult.at<uchar>(h,w) != 0)
                voteCounts[gs.labelMap.at<int>(h,w)]++;
        }
    }

    // superpixel movement decision
    vector<double> p(numClusters);
    vector<bool> clusterMoving(numClusters);
    for(int i = 0; i < numClusters; i++) {
    	p[i] = 0;
    	if(labelCounts[i] > 0)
    		p[i] = (double)voteCounts[i] / labelCounts[i];
    	clusterMoving[i] = false;
        if(p[i] >= thresh)
            clusterMoving[i] = true;
    }

    // generating segmentation mask
    segMask = cv::Mat::zeros(frame.size(), CV_8U);
    for(int h = 0; h < frame.rows; h++) {
        for(int w = 0; w < frame.cols; w++) {
        	if(clusterMoving[gs.labelMap.at<int>(h,w)])
        		segMask.at<uchar>(h,w) = 255;
        }
    }
}

double VotingSegmenter::getThreshold() {
	return thresh;
}

void VotingSegmenter::setThreshold(double thresh) {
	this->thresh = thresh;
}
