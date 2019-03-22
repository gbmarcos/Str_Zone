#ifndef BUSCADCONT_H
#define BUSCADCONT_H

#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class BuscadCont
{
public:
    BuscadCont();
    void setThreshold(double t);
    double getThreshold();
    void setHistogram(const cv::MatND& h);
    cv::Mat find(const cv::Mat& image,float minValue,float maxValue, int dim);

private:
    float hranges[2];
    const float* ranges[3];
    int channels[3];
    float threshold;
    cv::MatND histogram;
};

#endif // BUSCADCONT_H
