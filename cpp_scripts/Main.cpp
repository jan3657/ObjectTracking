#include <iostream>
#include "MeanShift.cpp"
#include <vector>
#include <time.h>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace cv;
int main(int argc, char** argv )
{
    std::ifstream ground_truth_capture;
    //VideoCapture capture("../data/ants/%08d.jpg" );    
    //ground_truth_capture = std::ifstream("../data/ants/groundtruth.txt");
    VideoCapture capture("../data/hand/%08d.jpg" );    
    ground_truth_capture = std::ifstream("../data/hand/groundtruth.txt");
    //VideoCapture capture("../data/cars.mp4");
    //VideoCapture capture(0);
    int frame_rate = 300000;
    
    std::vector<MeanShift> rectangles; //Vector where we're gonna push rectangles

    Mat frame;
    capture >> frame ;
    //If we don't have the first location, select it manually
    if (!ground_truth_capture.is_open()){
        for(int i = 0; i< 3; i++){
            Rect2d rect = selectROI("select",frame, false); //select a rectangle 
            rectangles.push_back(MeanShift(rect)); //add selected rectangle to the array
            destroyWindow("select");
            rectangle(frame, rect, Scalar(0,0,255), 4);
        }
    }
    
    
    
    clock_t start;
    clock_t end;
    double ms, fpsLive;

    

    if (!capture.isOpened())
        std::cout << "Unable to open the video" << std::endl; //Error opening the video

    
    else{
        std::cout << "Tracking" << std::endl;
        std::string line; 
        bool first = true;
        while(!frame.empty()){
            // If we have ground truth data, draw the rectangles.
            if (ground_truth_capture.is_open()){
                std::getline(ground_truth_capture, line);
                std::stringstream ss(line);
                std::vector<double> ground_truth_coordinates;
                while(ss.good()){
                    std::string substr;
                    std::getline(ss, substr, ',');
                    ground_truth_coordinates.push_back( std::stod(substr) );
                }
                Rect ground_truth_rect = Rect(ground_truth_coordinates[0],ground_truth_coordinates[1],ground_truth_coordinates[2],ground_truth_coordinates[3]);
                rectangle(frame, ground_truth_rect, Scalar(0,255,0), 4);
                if(first){
                    rectangles.push_back(MeanShift(ground_truth_rect));
                    imshow("tracking", frame);
                    waitKey(0);
                    first = false;
                }
            }
            
            start = clock(); 

            

            for(auto & elem : rectangles)
            {  
                elem.setFrame(frame);
                elem.track();
                rectangle(frame, elem.getTrackWindow(), Scalar(0,0,255), 4);

                //Point2f* points = elem.getTrackWindow();
                //for (int i = 0; i < 4; i++)
                //    line(frame, points[i], points[i+1%4] , 255, 2);
            }

            //FPS COUNTER
            do{
                fpsLive = double(1) / ((double(clock()) - double(start)) / double(CLOCKS_PER_SEC));

            }while(fpsLive > frame_rate);

            putText(frame, "FPS: " + std::to_string(int(fpsLive)), { 50, 50 }, FONT_HERSHEY_SIMPLEX, 1.5,2);

            
            //Show the image
            imshow("tracking", frame);
            int keyboard = waitKey(30);
            if (keyboard == 'q' || keyboard == 27)
                break;

            //Get new frame
            capture >> frame;
        }
    }
}