#pragma once

#include <opencv2/opencv.hpp>

class MeanShiftImp {
private:
    cv::Rect mTrack_window;
    cv::Mat mFrame, mRoi, mHsv_roi, mMask, mRoi_hist;

public:
    MeanShiftImp(cv::Rect mTrack_window);
    void track();
    void setFrame(cv::Mat mFrame);
    cv::Rect getTrackWindow();
};
