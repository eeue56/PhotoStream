#ifndef ROISELECTOR_H
#define ROISELECTOR_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

typedef struct {
    int left_x;
    int left_y;
    int right_x;
    int right_y;
} roi_values;

class RoiSelector {
public:
    RoiSelector(Mat image);
    void main_loop();
    roi_values roi;
    int points_down;
private:
    string window_name;
    Mat image;
};

Rect roi_as_rect(roi_values roi);

#endif // ROISELECTOR_H
