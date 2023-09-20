#include <stdio.h>
#include <string>
#include <vector>
#include <cassert>
#include "screenshot.hpp"

Screenshot::Screenshot(int x, int y, int width, int height):
    x(x),
    y(y),
    width(width),
    height(height)
{
    this->display = XOpenDisplay(nullptr);
    assert(this->display);
    this->root = RootWindow(this->display, DefaultScreen(this->display));
}

Screenshot::~Screenshot()
{
    if (image != nullptr)
        XDestroyImage(image);
    XCloseDisplay(this->display); 
}

cv::Mat Screenshot::takeScreenshot()
{
    this->image = XGetImage(this->display, this->root, this->x, this->y, this->width, this->height, AllPlanes, ZPixmap);
    return cv::Mat(this->height, this->width, CV_8UC4, this->image->data);
}

void Screenshot::findWindow(Window window, std::string &windowName, Window* windowReturn)
{
    XTextProperty text;
    XGetWMName(this->display, window, &text);
    char* name;
    XFetchName(this->display, window, &name);

    std::string current_name;
    current_name.copy((char *)(text.value), text.nitems);
    std::cout << text.value << std::endl;
    if (current_name.find(windowName) != std::string::npos)
    {
        std::cout << windowName << " found"  << std::endl;
        Window* necroWindow = new Window;
        std::cout << windowName << " yes"  << std::endl;
        *necroWindow = window;
        windowReturn = necroWindow;
        return;
    }

    Window root_return, parent_return;
    Window *children_return;
    unsigned int n_chidlren_return;
    XQueryTree(this->display, window, &root_return, &parent_return, &children_return, &n_chidlren_return);
    if (children_return != NULL) {
        for (int i = 0; i < n_chidlren_return; i++) {
            this->findWindow(children_return[i], windowName, windowReturn);
        }
        XFree(children_return);
    }
    return;
}

void Screenshot::getNecroWindow()
{
    XSynchronize(this->display, true);

    std::string necro_window_name ("Crypt");
    Window* necroWindow;
    findWindow(this->root, necro_window_name, necroWindow);

    XWindowAttributes window_attributes_return;
    XImage *current_image = XGetImage(
        this->display,
        *necroWindow,
        window_attributes_return.x,
        window_attributes_return.y,
        window_attributes_return.width,
        window_attributes_return.height,
        AllPlanes,
        ZPixmap
    );
    if (current_image == NULL) {
        std::cout << "Error: XGetImage returned:" << current_image << std::endl;
        return;
    }

    std::cout << "get image passed" << std::endl;
    cv::Mat mat = cv::Mat(
        window_attributes_return.width,
        window_attributes_return.height,
        CV_8UC4,
        current_image->data
    );
    cv::imshow("mat", mat);
    char k = cv::waitKey(5);

    delete necroWindow;
}
