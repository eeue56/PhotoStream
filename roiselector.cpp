#include "roiselector.h"

void mouse_callback(int event, int x, int y, int flags, void * selector){
    RoiSelector * roi_selector = (RoiSelector *) selector;

    if (roi_selector->points_down == 1) {
        roi_selector->roi.right_x = x;
        roi_selector->roi.right_y = y;
    }
    else if(roi_selector->points_down == 0) {
        roi_selector->roi.left_x = x;
        roi_selector->roi.left_y = y;
        roi_selector->roi.right_x = x;
        roi_selector->roi.right_y = y;
    }

    if (event != EVENT_LBUTTONDOWN){
        if(event == EVENT_RBUTTONDOWN){
            roi_selector->roi.left_x = 0;
            roi_selector->roi.left_y = 0;
            roi_selector->roi.right_x = 0;
            roi_selector->roi.right_y = 0;

            roi_selector->points_down = 0;
        }
    }
    else {
        if (roi_selector->points_down == 2){
            roi_selector->roi.right_x = x;
            roi_selector->roi.right_y = y;
        }
        else {
            roi_selector->points_down++;
        }
    }
}

RoiSelector::RoiSelector(Mat image) {
    this->window_name = "ROI_SELECTOR";
    this->points_down = 0;
    this->image = image;
}

void RoiSelector::main_loop() {
    namedWindow(this->window_name, CV_WINDOW_NORMAL);
    setMouseCallback(this->window_name, mouse_callback, this);

    Mat imageCopy;
    const int pause_key = 32;
    int key;

    while (true){
        this->image.copyTo(imageCopy);


        if (this->points_down > 0){
            rectangle(imageCopy,
                      Point(this->roi.left_x, this->roi.left_y),
                      Point(this->roi.right_x, this->roi.right_y),
                      Scalar(0, 255, 255),
                      4,
                      8
            );
        }

        imshow(this->window_name, imageCopy);
        key = waitKey(40);

        if (key == pause_key){
            break;
        }
    }

    destroyWindow(this->window_name);
    this->image.release();
}

Rect roi_as_rect(roi_values roi){
    int x = roi.left_x;
    int y = roi.left_y;
    int width = roi.right_x - x;
    int height = roi.right_y - y;

    if (roi.left_x > roi.right_x){
        x = roi.right_x;
        width = roi.left_x - x;
    }

    if (roi.left_y > roi.right_y){
        y = roi.right_y;
        height = roi.left_y - y;
    }

    return Rect(x, y, width, height);
}
