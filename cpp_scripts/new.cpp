#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "colotracker.h"
#include "region.h"
#include <string>

using namespace cv;

bool g_trackerInitialized = false;
ColorTracker *g_tracker = NULL;


int main(int argc, char **argv) 
{
    BBox * bb = NULL;
    cv::Mat img;
    int captureDevice = 0;
    if (argc > 1)
        captureDevice = atoi(argv[1]);

    cv::VideoCapture webcam = cv::VideoCapture(captureDevice);
    webcam.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    webcam.set(CAP_PROP_FRAME_HEIGHT, 480);
    if (!webcam.isOpened()){
        webcam.release();
        std::cerr << "Error during opening capture device!" << std::endl;
        return 1;
    }

    webcam >> img; 
    Rect selected_rect = selectROI("select",img, false); //select a rectangle 
    g_tracker = new ColorTracker(img, selected_rect);
    g_trackerInitialized = true;

    while(true){

        webcam >> img; 

        int c = waitKey(10);
        if(c == 27 ) { //if esc
            std::cout << "Exiting ..." << std::endl;
            break;
        }
        else if(c == 105) { //if i
            g_trackerInitialized = false;
 
        }

        if (g_trackerInitialized && g_tracker != NULL){
            cv::Rect *rect = g_tracker->track(img);
            rectangle(img, *rect, Scalar(0,0,255), 4);
            //bb->setBBox((double)rect.x,(double)rect.y,(double)rect.height,(double)rect.width,(double)1,(double)1);
        }

        if (bb != NULL){
            cv::rectangle(img, Point2i(bb->x, bb->y), Point2i(bb->x + bb->width, bb->y + bb->height), Scalar(255, 0, 0), 3);
            delete bb;
            bb = NULL;
        }

        cv::imshow("output", img);

    }

    if (g_tracker != NULL)
        delete g_tracker;
    return 0;
}
