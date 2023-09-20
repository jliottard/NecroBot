#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>
#include "detection/detect.cpp"
#include "capture/screenshot.cpp"

int main() {

    int width = 1920;
    int height = 1080;
    Screenshot screenshot(0, 0, width, height);

    while(true) 
    {
        cv::Mat cv_image = screenshot.takeScreenshot();
        cv::imshow("Screenshot", cv_image);

        char k = cv::waitKey(1);

        if (k == 'a')
            break;
    }
    
    // Test detection lib
    cv::Mat playerImage = cv::imread("../img/carence.png", cv::IMREAD_COLOR);
    cv::Mat gameImage = cv::imread("../img/game_screenshot_example.png", cv::IMREAD_COLOR);
    cv::Point detectionPoint = detect(playerImage, gameImage);
    std::cout << gameImage.rows << " " << gameImage.cols << std::endl;
    std::cout << detectionPoint << std::endl;

    return 0;
}
