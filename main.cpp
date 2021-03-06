#include <iostream>
#include <cstdlib>

#include "roiselector.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

#define detector_count 10

const string window_name = "main";
const string results_window_name = "results";

const string detector_types[] =
{
    "FAST",
    "STAR",
    "SIFT",
    "SURF",
    "ORB",
    "BRISK",
    "MSER",
    "GFTT",
    "HARRIS",
    "Dense",
    "SimpleBlob"
};
const int exit_key = 27;
const int pause_key = 32;


bool is_numerical(char * data){
    char * validator;
    strtol(data, &validator, 10);

    return !*validator;
}




int main(int argc, char * argv[]){
    roi_values roi;
    int image_index = 1;
    int selected_type = 1;
    Mat image;
    Mat roied_image;
    RoiSelector* selector;
    FeatureDetector* detector;
    cv::vector<KeyPoint> key_points;

    if (argc < 2){
        std::cout << "Not enough arguments" << std::endl;
        goto error;
    }


    if (is_numerical(argv[1])){
        std::cout << "Using parameters defined on command line" << std::endl;

        roi.left_x = atoi(argv[1]);
        roi.left_y = atoi(argv[2]);
        roi.right_x = atoi(argv[3]);
        roi.right_y = atoi(argv[4]);

        image_index = 5;
    }

    if (argc < 6){
        std::cout << "No image file provided." << std::endl;
        goto error;
    }

    image = imread(argv[image_index], CV_LOAD_IMAGE_COLOR);

    if (!image.data){
        std::cout << "Bad file!" << std::endl;
        goto error;
    }

    selector = new RoiSelector(image);

    selector->main_loop();

    roi = selector->roi;

    roied_image = image(roi_as_rect(roi));

    std::cout << "Creating detector" << std::endl;
    detector = FeatureDetector::create(detector_types[0]);

    std::cout << "Detecting keypoints" << std::endl;
    //detector->detect(roied_image, key_points);

    std::cout << "Finished detecting" << std::endl;
    //std::cout << key_points.size() << std::endl;


    namedWindow(window_name, CV_WINDOW_NORMAL);
    createTrackbar("Descriptor type", window_name, &selected_type, detector_count);

    while (true){
        imshow(window_name, roied_image);


        waitKey(0);

        std::cout << "Hello: " << detector_types[selected_type] << std::endl;
    }

    return 0;

    error: {
        return -1;
    }
}
