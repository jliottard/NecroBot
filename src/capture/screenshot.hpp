#ifndef SCREENSHOT_HPP
#define SCREENSHOT_HPP

#include <string>

// Image manipulation
#include <opencv2/opencv.hpp>   // this header must be included before X11 includes

// Image recording for linux
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class Screenshot
{
    Display* display;
    Window root;
    XImage* image{nullptr};
    int x, y, width, height;

public:
    Screenshot(int x, int y, int width, int height);
    ~Screenshot();

    cv::Mat takeScreenshot();
    void getNecroWindow();
private:
    void findWindow(Window window, std::string &windowName, Window* windowReturn);
};

#endif
