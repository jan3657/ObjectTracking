#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "MeanShift.h"
#include <time.h>
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
            double fps = capture.get(CAP_PROP_FPS);
            clock_t start;
            clock_t end;
            double ms, fpsLive;
        if (!this->capture.isOpened()){
        //error in opening the video input
        std::cout << "Unable to open file!" << std::endl;

        }
        else{
            std::cout << "Tracking" << std::endl;
            Mat frame, roi, hsv_roi, mask;
            this->capture >> frame;
            
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
                start = clock();
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
                //FPS COUNTER
                end = clock();
                double seconds =  (double(end) - double(start)) / double(CLOCKS_PER_SEC);
                fpsLive = double(1) / double(seconds);
                putText(frame, "FPS: " + std::to_string(int(fpsLive)), { 50, 50 }, FONT_HERSHEY_SIMPLEX, 1.5,2);
                
                //show img
                imshow("img", frame);
                int keyboard = waitKey(30);
                if (keyboard == 'q' || keyboard == 27)
                    break;
            }
        }
    }
        
};

