#include "detect.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

Point detect(Mat templateImage, Mat image) {
    int match_method = TM_SQDIFF;
    Mat img = image;
    Mat templ = templateImage;
    Mat result;

    Mat img_display;
    img.copyTo(img_display);
    
    int result_cols = image.cols - templateImage.cols + 1;
    int result_rows = image.rows - templateImage.rows + 1;

    result.create(result_rows, result_cols, CV_8UC3);

    matchTemplate(img, templ, result, match_method);

    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    matchLoc = minLoc;

    rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(255), 2, 8, 0);
    rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(255), 2, 8, 0);
    
    imwrite("ouput_img_display.png", img_display);
    imwrite("ouput_result.png", result);

    return matchLoc;
}