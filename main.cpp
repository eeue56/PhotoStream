#include <iostream>
#include <cstdlib>

#include "roiselector.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define MAX_THRESHOLD 255
#define MIN_THRESHOLD 0

using namespace cv;



bool is_numerical(char * data){
    char * validator;
    strtol(data, &validator, 10);

    return !*validator;
}


int main(int argc, char * argv[]){
    const string window_name = "main";
    const string results_window_name = "results";
    const int exit_key = 27;
    const int pause_key = 32;

    roi_values roi;
    int image_index = 1;
    Mat image;
    Mat roied_image;
    RoiSelector* selector;

    std::cout << "here" << std::endl;

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


    namedWindow(window_name, CV_WINDOW_NORMAL);
    imshow(window_name, roied_image);

    waitKey(0);

    return 0;

    error: {
        return -1;
    }
}
