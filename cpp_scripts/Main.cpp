#include <iostream>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "MeanShiftImp.h"
#include "CamShiftImp.h"
#include "colotracker.h"

using namespace cv;
ColorTracker *g_tracker = NULL;
int main(int argc, char* argv[])
{
    enum algorithms {
        mean_shift,
        cam_shift
    };
   
    
    std::ifstream ground_truth_capture;
    VideoCapture capture(0);
    capture.set(CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CAP_PROP_FRAME_HEIGHT, 480);
    int number_of_tracking_objects = 1;
    int frame_rate = 300000;
    algorithms tracking_algorithm = mean_shift;

    for (int i = 0; i < argc; ++i){
        if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--source") == 0){
            std::string video_path = argv[i+1] + std::string("/\%08d.jpg");
            std::string ground_truth_path = argv[i+1] + std::string("/groundtruth.txt");
            capture = VideoCapture(video_path);
            
            ground_truth_capture = std::ifstream(ground_truth_path);
            
        }

        else if(strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0){
            number_of_tracking_objects = std::stoi(argv[i+1]);
        }

        else if(strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--algorithm") == 0){
            std::string value = argv[i+1];
            static std::unordered_map<std::string, algorithms> const table = { {"mean_shift",algorithms::mean_shift}, {"cam_shift",algorithms::cam_shift} };
            auto it = table.find(value);
            if (it != table.end()) {
                tracking_algorithm = it->second;
                
            } else { 
                std::cout << "You misspelled algorithm name or used unsuported one" << std::endl;
            }
        }
    }
        
    //VideoCapture capture("../data/hand/%08d.jpg" );    
    //ground_truth_capture = std::ifstream("../data/hand/groundtruth.txt");
   
    std::vector<ColorTracker> color_trackers;
    std::vector<MeanShiftImp> mean_shift_trackers; 
    std::vector<CamShiftImp> cam_shift_trackers;

    Mat frame;
    capture >> frame ;
    if (!ground_truth_capture.is_open()){ //If we don't have the first location, select it manually
        for(int i = 0; i < number_of_tracking_objects; i++){
            Rect rect = selectROI("select",frame, false); //select a rectangle 
            g_tracker = new ColorTracker(frame, rect);
            mean_shift_trackers.push_back(MeanShiftImp(rect));
            cam_shift_trackers.push_back(CamShiftImp(rect));
            color_trackers.push_back(*g_tracker);
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
        

        if(tracking_algorithm == mean_shift){
            std::cout << "Tracking with : mean_shift" << std::endl;
        }else if (tracking_algorithm == cam_shift){
            std::cout << "Tracking with : cam_shift" << std::endl;
        }
            
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
                    cam_shift_trackers.push_back(CamShiftImp(ground_truth_rect));
                    mean_shift_trackers.push_back(MeanShiftImp(ground_truth_rect));
                    imshow("tracking", frame);
                    waitKey(0);
                    first = false;
                }
            }
            
            start = clock(); 

            if (tracking_algorithm == algorithms::mean_shift){
                for(auto & elem : color_trackers){  
                    Rect *rect = g_tracker->track(frame);
                    rectangle(frame, *rect, Scalar(0,0,255), 4);
                }

            }
            else if (tracking_algorithm == algorithms::cam_shift){
                for(auto & elem : cam_shift_trackers){  
                    //elem.setFrame(frame);
                    elem.track(frame);
                    rectangle(frame, elem.getTrackWindow(), Scalar(0,0,255), 4);
                }
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