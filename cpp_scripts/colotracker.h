#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "histogram.h"
#include <iostream>


//#define SHOWDEBUGWIN

#define BIN_1 16
#define BIN_2 16
#define BIN_3 16

class ColorTracker
{
private:
    cv::Rect mTrack_window;
    double total_fps = 0;
    int iterations = 0;
    cv::Rect lastPosition;
    cv::Rect tracking_window;
    cv::Mat im1;
    cv::Mat im2;
    cv::Mat im3;

    cv::Mat im1_old;
    cv::Mat im2_old;
    cv::Mat im3_old;

    Histogram q_hist;
    Histogram q_orig_hist;
    Histogram b_hist;

    double defaultWidth;
    double defaultHeight;

    double wAvgBg;
    double bound1;
    double bound2;

    cv::Point histMeanShift(double x1, double y1, double x2, double y2);
    cv::Point histMeanShiftIsotropicScale(double x1, double y1, double x2, double y2, double * scale, int * msIter = NULL);
    cv::Point histMeanShiftAnisotropicScale(double x1, double y1, double x2, double y2, double * width, double * height);

    void preprocessImage(cv::Mat & img);
    void extractBackgroundHistogram(int x1, int y1, int x2, int y2, Histogram &hist);
    void extractForegroundHistogram(int x1, int y1, int x2, int y2, Histogram &hist);

    inline double kernelProfile_Epanechnikov(double x)
        { return (x <= 1) ? (2.0/3.14)*(1-x) : 0; }
        //{ return (x <= 1) ? (1-x) : 0; }
    inline double kernelProfile_EpanechnikovDeriv(double x)
        { return (x <= 1) ? (-2.0/3.14) : 0; }
        //{ return (x <= 1) ? -1 : 0; }
public:
    int frame;
    int sumIter;

    void init(cv::Mat & img, cv::Rect selected);
    ColorTracker(cv::Mat & img, cv::Rect mTrack_window);



	// frame-to-frame object tracking
    cv::Rect *track(cv::Mat &img, double x1, double y1, double x2, double y2);
    inline cv::Rect *track(cv::Mat &img)
    {
        return track(img, lastPosition.x, lastPosition.y, lastPosition.x + lastPosition.width, lastPosition.y + lastPosition.height);
    }
};

