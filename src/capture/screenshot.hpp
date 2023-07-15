#ifndef SCRENSHOT_HPP
#define SCRENSHOT_HPP

#include <cassert>

// Image manipulation
#include <opencv2/opencv.hpp>   // this header must be included before X11 includes

// Image recording for linux
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

class Screenshot
{
    Display* display;
    Window root;
    XImage* image{nullptr};
    int x, y, width, height;

public:
    Screenshot(int x, int y, int width, int height):
        x(x),
        y(y),
        width(width),
        height(height)
    {
        this->display = XOpenDisplay(nullptr);
        assert(this->display);
        this->root = RootWindow(this->display, DefaultScreen(this->display));
    }

    ~Screenshot()
    {
        if (image != nullptr)
            XDestroyImage(image);
        XCloseDisplay(this->display);
    }

    cv::Mat takeScreenshot()
    {
        this->image = XGetImage(this->display, this->root, this->x, this->y, this->width, this->height, AllPlanes, ZPixmap);
        return cv::Mat(this->height, this->width, CV_8UC4, this->image->data);
    }
};

#endif
