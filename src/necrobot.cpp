#include <opencv2/opencv.hpp>
#include "detection/capture.h"
#include "detection/detect.h"

int main() {

    // Test screenshot lib
    cv::Mat screenshot = getScreenShot();
    cv::imwrite("screenshot.jpg", screenshot);

    // Test detection lib
    cv::Mat playerImage = cv::imread("../img/carence.png", cv::IMREAD_COLOR);
    cv::Mat gameImage = cv::imread("../img/game_screenshot_example.png", cv::IMREAD_COLOR);
    cv::Point detectionPoint = detect(playerImage, gameImage);
    std::cout << gameImage.rows << " " << gameImage.cols << std::endl;
    std::cout << detectionPoint << std::endl;


    return 0;
}

