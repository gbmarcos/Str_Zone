#ifndef IMAGECOMPARATOR_H
#define IMAGECOMPARATOR_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <histog1d.h>

class ImageComparator
{
private:
    cv::Mat reference;
    cv::Mat input;
    cv::MatND refH;
    cv::MatND inputH;
    Histog1D hist;
    int div;
public:
    ImageComparator();
    void setColorReduction( int factor);
    int getColorReduction();
    void setReferenceImage(const cv::Mat& image);
    double compare(const cv::Mat& image);
};

#endif // IMAGECOMPARATOR_H
