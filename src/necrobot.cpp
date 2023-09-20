#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

#include "capture/screenshot.cpp"

int main() {

    int width = 1920;
    int height = 1080;
    Screenshot screenshot(0, 0, width, height);
    // screenshot.getNecroWindow();

    while(true) 
    {
        cv::Mat cv_image = screenshot.takeScreenshot();
        cv::imshow("Screenshot", cv_image);

        char k = cv::waitKey(1);

        if (k == 'a')
            break;
    }
    
    return 0;
}
