#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
class ColorDetector
{
public:
    ColorDetector();
    void setTargetColor(cv::Vec3b color);
    int getDistance(cv::Vec3b color);
    cv::Mat process(const cv::Mat &image);
    int getColorDistanceThreshold();
    void setColorDistanceThreshold(int distance);
    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    cv::Vec3b getTargetColor();
private:
    int minDist;
    cv::Vec3b target;
    cv::Mat result;



};

#endif // COLORDETECTOR_H
