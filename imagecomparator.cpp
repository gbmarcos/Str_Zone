#include "imagecomparator.h"

ImageComparator::ImageComparator(): div(32)
{

}

void ImageComparator::setColorReduction( int factor) {
    div= factor;
}

int ImageComparator::getColorReduction() {
    return div;
}

void ImageComparator::setReferenceImage(const cv::Mat& image) {
    //reference= hist.colorReduce(image,div);
    refH= hist.getHistogram(image);
}

double ImageComparator::compare(const cv::Mat& image) {
    //input= hist.colorReduce(image,div);
    inputH= hist.getHistogram(image);
    return cv::compareHist(refH,inputH,CV_COMP_INTERSECT);
}
