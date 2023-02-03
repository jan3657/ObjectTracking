#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "CamShiftImp.h"

using namespace cv;
CamShiftImp::CamShiftImp(Rect track_window) {
    this->mTrack_window = track_window;
}

void CamShiftImp::track(){     
    // set up the ROI for tracking
    mRoi = mFrame(mTrack_window);
    cvtColor(mRoi, mHsv_roi, COLOR_BGR2HSV);
    inRange(mHsv_roi, Scalar(0, 60, 32), Scalar(180, 255, 255), mMask);
    float range_[] = {0, 180};
    const float* range[] = {range_};
    Mat roi_hist;
    int histSize[] = {180};
    int channels[] = {0};
    calcHist(&mHsv_roi, 1, channels, mMask, roi_hist, 1, histSize, range);
    normalize(roi_hist, roi_hist, 0, 255, NORM_MINMAX);
    TermCriteria term_crit(TermCriteria::EPS | TermCriteria::COUNT, 10, 1);

    Mat mHsv, mDst;
    cvtColor(mFrame, mHsv, COLOR_BGR2HSV);
    calcBackProject(&mHsv, 1, channels, roi_hist, mDst, range);
    //apply camshift to get the new location
    RotatedRect rot_rect = cv::CamShift(mDst, mTrack_window, term_crit);
}

void CamShiftImp::setFrame(Mat frame){
    this->mFrame = frame;
}

Rect CamShiftImp::getTrackWindow(){
    return mTrack_window;
}