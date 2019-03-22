#ifndef SEGMENTADORWS_H
#define SEGMENTADORWS_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class SegmentadorWS
{
public:
    SegmentadorWS();
    void setMarkers(const cv::Mat& markerImage);
    cv::Mat process(const cv::Mat &image);



private:
    cv::Mat markers;
};

#endif // SEGMENTADORWS_H
