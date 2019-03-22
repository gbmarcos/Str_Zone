#include "colordetector.h"
#include <QColorDialog>

ColorDetector::ColorDetector() : minDist(100){
    // default parameter initialization here
    target[0]= target[1]= target[2]= 0;
}

void ColorDetector::setColorDistanceThreshold(int distance) {
    if (distance<0)
        distance=0;
    minDist= distance;
}

int ColorDetector::getColorDistanceThreshold()  {
    return minDist;
}

void  ColorDetector::setTargetColor(unsigned char red, unsigned char green, unsigned char blue) {
    // BGR order
    target[2]= red;
    target[1]= green;
    target[0]= blue;
}

void ColorDetector::setTargetColor(cv::Vec3b color) {
    target= color;
}

cv::Vec3b ColorDetector::getTargetColor()  {
    return target;
}
cv::Mat ColorDetector::process(const cv::Mat &image) {

    result.create(image.rows,image.cols,CV_8U);

    cv::Mat_<cv::Vec3b>::const_iterator it= image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itend= image.end<cv::Vec3b>();
    cv::Mat_<uchar>::iterator itout= result.begin<uchar>();

    for ( ; it!= itend; ++it, ++itout) {
        if (getDistance(*it)<minDist) {
            *itout=255;
        }else{
            *itout= 0;
        }

    }
    return result;
}

int ColorDetector::getDistance(cv::Vec3b color){
    return static_cast<int>(cv::norm<int,3>(cv::Vec3i(color[0]-target[0],color[1]-target[1],color[2]-target[2])));
}
