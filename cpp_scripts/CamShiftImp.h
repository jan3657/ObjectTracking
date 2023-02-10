#pragma once

#include <opencv2/opencv.hpp>

class CamShiftImp {
private:
    cv::Rect mTrack_window;
    cv::Mat mFrame, mRoi, mHsv_roi, mMask, mRoi_hist;

public:
    CamShiftImp(cv::Rect mTrack_window);
    void track(cv::Mat &img);
    cv::Rect getTrackWindow();
};
