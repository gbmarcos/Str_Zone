#include "segmentadorws.h"

SegmentadorWS::SegmentadorWS()
{
}

void SegmentadorWS::setMarkers(const cv::Mat &markerImage)
{

    markerImage.convertTo(markers,CV_32S);

}

cv::Mat SegmentadorWS::process(const cv::Mat &image)
{

    cv::watershed(image,markers);

    return markers;
}
