#ifndef LAPLACIANZC_H
#define LAPLACIANZC_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
class LaplacianZC
{
public:
    LaplacianZC();
    void setAperture(int a);
    cv::Mat computeLaplacian(const cv::Mat& image);
    cv::Mat getLaplacianImage(double scale=-1.0);

private:
    cv::Mat img;
    cv::Mat laplace;
    int aperture;
};

#endif // LAPLACIANZC_H
