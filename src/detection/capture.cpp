#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include "capture.h"

void imageFromDisplay(std::vector<uint8_t>& pixels, int& width, int& height, int& bitsPerPixel) {
    Display* display = XOpenDisplay(nullptr);

    if (display == nullptr) {
        std::cout << "Display is " << display << std::endl;
        return;
    }

    Window root = DefaultRootWindow(display);

    XWindowAttributes attributes = {0};
    XGetWindowAttributes(display, root, &attributes);

    width = attributes.width;
    height = attributes.height;

    XImage* img = XGetImage(display, root, 0, 0 , width, height, AllPlanes, ZPixmap);
    bitsPerPixel = img->bits_per_pixel;
    pixels.resize(width * height * 4);

    memcpy(&pixels[0], img->data, pixels.size());

    XDestroyImage(img);
    XCloseDisplay(display);
}

cv::Mat getScreenShot(void) {
    int width = 0;
    int height = 0;
    int Bpp = 0;
    std::vector<std::uint8_t> pixels;
    imageFromDisplay(pixels, width, height, Bpp);

    cv::Mat img = cv::Mat(height, width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &pixels[0]);

    return img;
}