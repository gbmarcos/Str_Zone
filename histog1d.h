#ifndef HISTOG1D_H
#define HISTOG1D_H

#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class Histog1D
{
public:

    Histog1D();
    cv::MatND getHistogram(const cv::Mat &image);
    cv::Mat getHistogramImage(const cv::Mat &image);
    cv::Mat applyLookUp(const cv::Mat& image,const cv::Mat& lookup);
    cv::Mat stretch(const cv::Mat &image, int minValue);
    cv::Mat equalize(const cv::Mat &image);
    cv::MatND getHueHistogram(const cv::Mat &image, int minSaturation);
private:
    int histSize[1];

    float hranges[2];

    const float* ranges[1];

    int channels[1];

};

#endif // HISTOG1D_H
