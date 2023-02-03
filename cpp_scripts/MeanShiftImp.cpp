#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "MeanShiftImp.h"

using namespace cv;
 

MeanShiftImp::MeanShiftImp(Rect mTrack_window) {
    this->mTrack_window = mTrack_window;
}   

void MeanShiftImp::track(){     
    
    mRoi = mFrame(mTrack_window);
    cvtColor(mRoi, mHsv_roi, COLOR_BGR2HSV);
    inRange(mHsv_roi, Scalar(0, 60, 32), Scalar(180, 255, 255), mMask);

    int histSize[] = {180};
    int channels[] = {0};
    float range_[] = {0, 180};
    const float* range[] = {range_};
    TermCriteria term_crit(TermCriteria::EPS | TermCriteria::COUNT, 10, 1);
    
    calcHist(&mHsv_roi, 1, channels, mMask, mRoi_hist, 1, histSize, range);
    normalize(mRoi_hist, mRoi_hist, 0, 255, NORM_MINMAX);

    Mat mHsv, mDst;
    cvtColor(mFrame, mHsv, COLOR_BGR2HSV);
    calcBackProject(&mHsv, 1, channels, mRoi_hist, mDst, range);
    meanShift(mDst, mTrack_window, term_crit);
}

void MeanShiftImp::setFrame(Mat frame){
    this->mFrame = frame;
}

Rect MeanShiftImp::getTrackWindow(){
    return(mTrack_window);
    }
    

