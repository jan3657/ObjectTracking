#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "MeanShift.cpp"

using namespace cv;
int main(int argc, char** argv )
{
    VideoCapture capture("../data/cars.mp4");
    //VideoCapture capture(0);
    Mat frame;
    capture >> frame ;
    Rect2d rect = selectROI(frame, false); 
                                     
    rectangle(frame, rect, Scalar(0,0,255), 4);

    Scalar roi(rect.x,rect.y,rect.width,rect.height);
    MeanShift tracker1( rect, capture);
    std::cout<<"Tracking"<<std::endl;
    tracker1.track();
    
}