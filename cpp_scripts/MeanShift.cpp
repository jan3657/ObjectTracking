#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "MeanShift.h"
using namespace cv;

class MeanShift{
    public:
    VideoCapture capture;
    Rect track_window;
    MeanShift(Rect track_window, VideoCapture capture) {
        this->track_window = track_window;
        this->capture = capture;
    }

    public:
        void track(){
        if (!this->capture.isOpened()){
        //error in opening the video input
        std::cout << "Unable to open file!" << std::endl;

        }
        else{
            std::cout << "Tracking" << std::endl;
            Mat frame, roi, hsv_roi, mask;
            this->capture >> frame;
            
            //Rect track_window(896, 297, 212, 166); //Hardcoded coordinates for tracking

            // set up the ROI for tracking
            roi = frame(this->track_window);
            cvtColor(roi, hsv_roi, COLOR_BGR2HSV);
            inRange(hsv_roi, Scalar(0, 60, 32), Scalar(180, 255, 255), mask);

            float range_[] = {0, 180};
            const float* range[] = {range_};
            Mat roi_hist;
            int histSize[] = {180};
            int channels[] = {0};
            calcHist(&hsv_roi, 1, channels, mask, roi_hist, 1, histSize, range);
            normalize(roi_hist, roi_hist, 0, 255, NORM_MINMAX);
            TermCriteria term_crit(TermCriteria::EPS | TermCriteria::COUNT, 10, 1);

            while(true){
                Mat hsv, dst;
                this->capture >> frame;
                if (frame.empty())
                    break;
                cvtColor(frame, hsv, COLOR_BGR2HSV);
                calcBackProject(&hsv, 1, channels, roi_hist, dst, range);
                // apply meanshift to get the new location
                meanShift(dst, this->track_window, term_crit);
                // Draw it on image
                rectangle(frame, this->track_window, Scalar(0,0,255), 4);
                imshow("img2", frame);
                int keyboard = waitKey(30);
                if (keyboard == 'q' || keyboard == 27)
                    break;
            }
        }
    }
        
};

