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
const std::string YOLO_VERSION = "v4-tiny";
const std::vector<cv::Scalar> colors = {cv::Scalar(255, 255, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 255, 255), cv::Scalar(255, 0, 0)};

std::vector<std::string> load_class_list()
{
    std::vector<std::string> class_list;
    std::ifstream ifs("./config_files/classes.txt");
    std::string line;
    while (getline(ifs, line))
    {
        class_list.push_back(line);
    }
    return class_list;
}
void load_net(cv::dnn::Net &net)
{
    auto result = cv::dnn::readNetFromDarknet("./config_files/yolo" + YOLO_VERSION + ".cfg", "./config_files/yolo" + YOLO_VERSION + ".weights");
    std::cout << "Running on CPU\n";
    result.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    result.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    net = result;
}

int main(int argc, char *argv[])
{
    enum algorithms
    {
        mean_shift,
        cam_shift,
        asms,
        yolov4
    };

    std::ifstream ground_truth_capture;
    VideoCapture capture(0);
    capture.set(CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CAP_PROP_FRAME_HEIGHT, 480);
    int number_of_tracking_objects = 1;
    int number_of_frames = 0;
    const int frame_rate = 300000;
    algorithms tracking_algorithm = mean_shift;

    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--source") == 0)
        {
            std::string video_path = argv[i + 1] + std::string("/\%08d.jpg");
            std::string ground_truth_path = argv[i + 1] + std::string("/groundtruth.txt");
            capture = VideoCapture(video_path);

            ground_truth_capture = std::ifstream(ground_truth_path);
        }

        else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0)
        {
            number_of_tracking_objects = std::stoi(argv[i + 1]);
        }

        else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--algorithm") == 0)
        {
            std::string value = argv[i + 1];
            static std::unordered_map<std::string, algorithms> const table = {{"mean_shift", algorithms::mean_shift}, {"cam_shift", algorithms::cam_shift}, {"asms", algorithms::asms}, {"yolov4", algorithms::yolov4}};
            auto it = table.find(value);
            if (it != table.end())
            {
                tracking_algorithm = it->second;
            }
            else
            {
                std::cout << "You misspelled algorithm name or used unsuported one" << std::endl;
            }
        }
    }

    // VideoCapture capture("../data/hand/%08d.jpg" );
    if (tracking_algorithm == yolov4)
    {
        std::vector<std::string> class_list = load_class_list();

        cv::Mat frame;
        if (!capture.isOpened())
        {
            std::cerr << "Error opening video file\n";
            return -1;
        }

        cv::dnn::Net net;
        load_net(net);

        auto model = cv::dnn::DetectionModel(net);
        model.setInputParams(1. / 255, cv::Size(416, 416), cv::Scalar(), true);

        auto start = std::chrono::high_resolution_clock::now();
        int frame_count = 0;
        float fps = -1;
        int total_frames = 0;

        while (true)
        {
            capture.read(frame);
            if (frame.empty())
            {
                std::cout << "End of stream\n";
                break;
            }

            std::vector<int> classIds;
            std::vector<float> confidences;
            std::vector<cv::Rect> boxes;
            model.detect(frame, classIds, confidences, boxes, .2, .4);
            frame_count++;
            total_frames++;

            int detections = classIds.size();

            for (int i = 0; i < detections; ++i)
            {

                auto box = boxes[i];
                auto classId = classIds[i];
                const auto color = colors[classId % colors.size()];
                cv::rectangle(frame, box, color, 3);

                cv::rectangle(frame, cv::Point(box.x, box.y - 20), cv::Point(box.x + box.width, box.y), color, cv::FILLED);
                cv::putText(frame, class_list[classId].c_str(), cv::Point(box.x, box.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
            }

            if (frame_count >= 30)
            {

                auto end = std::chrono::high_resolution_clock::now();
                fps = frame_count * 1000.0 / std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                frame_count = 0;
                start = std::chrono::high_resolution_clock::now();
            }

            if (fps > 0)
            {

                std::ostringstream fps_label;
                fps_label << std::fixed << std::setprecision(2);
                fps_label << "FPS: " << fps;
                std::string fps_label_str = fps_label.str();

                cv::putText(frame, fps_label_str.c_str(), cv::Point(10, 25), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            }

            cv::imshow("output", frame);

            if (cv::waitKey(1) != -1)
            {
                capture.release();
                std::cout << "finished by user\n";
                break;
            }
        }
        std::cout << "Total frames: " << total_frames << "\n";

        return 0;
    }

    std::vector<ColorTracker> color_trackers;
    std::vector<MeanShiftImp> mean_shift_trackers;
    std::vector<CamShiftImp> cam_shift_trackers;

    Mat frame;
    capture >> frame;
    if (!ground_truth_capture.is_open())
    { // If we don't have the first location, select it manually
        for (int i = 0; i < number_of_tracking_objects; i++)
        {
            Rect rect = selectROI("select", frame, false); // select a rectangle
            mean_shift_trackers.push_back(MeanShiftImp(rect));
            cam_shift_trackers.push_back(CamShiftImp(rect));
            color_trackers.push_back(ColorTracker(frame, rect));
            destroyWindow("select");
            rectangle(frame, rect, Scalar(0, 0, 255), 4);
        }
    }

    clock_t start;
    double fpsLive;

    if (!capture.isOpened())
        std::cout << "Unable to open the video" << std::endl; // Error opening the video

    else
    {
        if (tracking_algorithm == mean_shift)
        {
            std::cout << "Tracking with : mean_shift" << std::endl;
        }
        else if (tracking_algorithm == cam_shift)
        {
            std::cout << "Tracking with : cam_shift" << std::endl;
        }
        else if (tracking_algorithm == asms)
        {
            std::cout << "Tracking with : asms" << std::endl;
        }

        std::string line;
        bool first = true;
        while (!frame.empty())
        {
            // If we have ground truth data, draw the rectangles.
            if (ground_truth_capture.is_open())
            {
                std::getline(ground_truth_capture, line);
                std::stringstream ss(line);
                std::vector<double> ground_truth_coordinates;
                while (ss.good())
                {
                    std::string substr;
                    std::getline(ss, substr, ',');
                    ground_truth_coordinates.push_back(std::stod(substr));
                }
                Rect ground_truth_rect = Rect(ground_truth_coordinates[0], ground_truth_coordinates[1], ground_truth_coordinates[2], ground_truth_coordinates[3]);
                rectangle(frame, ground_truth_rect, Scalar(0, 255, 0), 4);
                if (first)
                {
                    cam_shift_trackers.push_back(CamShiftImp(ground_truth_rect));
                    mean_shift_trackers.push_back(MeanShiftImp(ground_truth_rect));
                    color_trackers.push_back(ColorTracker(frame, ground_truth_rect));
                    imshow("tracking", frame);
                    waitKey(0);
                    first = false;
                }
            }

            start = clock();
            number_of_frames++;

            if (tracking_algorithm == algorithms::mean_shift)
            {
                for (auto &elem : mean_shift_trackers)
                {
                    elem.setFrame(frame);
                    elem.track();
                    rectangle(frame, elem.getTrackWindow(), Scalar(0, 0, 255), 4);
                }
            }
            else if (tracking_algorithm == algorithms::cam_shift)
            {
                for (auto &elem : cam_shift_trackers)
                {
                    // elem.setFrame(frame);
                    elem.track(frame);
                    rectangle(frame, elem.getTrackWindow(), Scalar(0, 0, 255), 4);
                }
            }
            if (tracking_algorithm == algorithms::asms)
            {
                for (auto &elem : color_trackers)
                {
                    Rect *rect = elem.track(frame);
                    rectangle(frame, *rect, Scalar(0, 0, 255), 4);
                }
            }

            // FPS COUNTER
            do
            {
                fpsLive = double(1) / ((double(clock()) - double(start)) / double(CLOCKS_PER_SEC));

            } while (fpsLive > frame_rate);

            putText(frame, "FPS: " + std::to_string(int(fpsLive)), {50, 50}, FONT_HERSHEY_SIMPLEX, 1.5, 2);

            // Show the image
            imshow("tracking", frame);
            int keyboard = waitKey(30);
            if (keyboard == 'q' || keyboard == 27)
                break;
            // save the image
            std::string imName = "/output/first/img" + std::to_string(number_of_frames) + ".jpg";
            imwrite(imName, frame);

            // Get new frame
            capture >> frame;
        }
    }
}