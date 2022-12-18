#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "MeanShift.h"

using namespace cv;

class CamShift{
    Mat frame, roi, hsv_roi, mask, roi_hist;
    Rect track_window;    
    
    public:   
    CamShift(Rect track_window) {
        this->track_window = track_window;
    }

    public:
    void track(){     
        // set up the ROI for tracking
        roi = frame(track_window);
        cvtColor(roi, hsv_roi, COLOR_BGR2HSV);
        inRange(hsv_roi, Scalar(0, 60, 32), Scalar(180, 255, 255), mask);

        int histSize[] = {180};
        int channels[] = {0};
        float range_[] = {0, 180};
        const float* range[] = {range_};

        //Setup the termination criteria, either 10 iteration or move by at least 1 pt
        TermCriteria term_crit(TermCriteria::EPS | TermCriteria::COUNT, 10, 1);
        
        calcHist(&hsv_roi, 1, channels, mask, roi_hist, 1, histSize, range);
        normalize(roi_hist, roi_hist, 0, 255, NORM_MINMAX);

        Mat hsv, dst;
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        calcBackProject(&hsv, 1, channels, roi_hist, dst, range);
        // apply meanshift to get the new location
        meanShift(dst, track_window, term_crit);
    }

    void setFrame(Mat frame){
        this->frame = frame;
    }

    Rect getTrackWindow(){
        return track_window;
    }
        
};

