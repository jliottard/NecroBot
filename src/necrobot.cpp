#include <opencv2/opencv.hpp>
#include "detection/capture.h"

int main() {

    cv::Mat screenshot = getScreenShot();
    cv::imwrite("screenshot.jpg", screenshot);

    return 0;
}

