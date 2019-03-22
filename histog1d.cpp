#include "histog1d.h"

Histog1D::Histog1D()
{
    histSize[0]= 256;
    hranges[0]= 0.0;
    hranges[1]= 255.0;
    ranges[0]= hranges;
    channels[0]= 0;
}
cv::MatND Histog1D::getHistogram(const cv::Mat &image){
    cv::MatND hist;
    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges);
    return hist;
}


cv::Mat Histog1D::getHistogramImage(const cv::Mat &image){


    cv::MatND hist= getHistogram(image);
    double maxVal=0;
    double minVal=0;
    cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
    cv::Mat histImg(histSize[0], histSize[0],
            CV_8U,cv::Scalar(255));

    int hpt = static_cast<int>(0.9*histSize[0]);

    for( int h = 0; h < histSize[0]; h++ ) {
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal*hpt/maxVal);

        cv::line(histImg,cv::Point(h,histSize[0]),
                cv::Point(h,histSize[0]-intensity),
                cv::Scalar::all(0));
    }
    return histImg;
}

cv::Mat Histog1D::applyLookUp(const cv::Mat& image,const cv::Mat& lookup) {

    cv::Mat result;
    cv::LUT(image,lookup,result);
    return result;
}

cv::Mat Histog1D::stretch(const cv::Mat &image, int minValue) {

    cv::MatND hist= getHistogram(image);

    int imin= 0;
    for( ; imin < histSize[0]; imin++ ) {
        std::cout<<hist.at<float>(imin)<<std::endl;
        if (hist.at<float>(imin) > minValue)
            break;
    }

    int imax= histSize[0]-1;
    for( ; imax >= 0; imax-- ) {
        if (hist.at<float>(imax) > minValue)
            break;
    }

    int dim(256);
    cv::Mat lookup(1, &dim, CV_8U);


    for (int i=0; i<256; i++) {

        if (i < imin) lookup.at<uchar>(i)= 0;
        else if (i > imax) lookup.at<uchar>(i)= 255;

        else lookup.at<uchar>(i)= static_cast<uchar>(
                    255.0*(i-imin)/(imax-imin)+0.5);
    }

    cv::Mat result;
    result= applyLookUp(image,lookup);
    return result;
}


cv::Mat Histog1D::equalize(const cv::Mat &image) {
    cv::Mat result;
    cv::equalizeHist(image,result);

    return result;
}

cv::MatND Histog1D::getHueHistogram(const cv::Mat &image, int minSaturation=0) {
    cv::MatND hist;

    cv::Mat hsv;
    cv::cvtColor(image, hsv, CV_BGR2HSV);
    cv::Mat mask;
    if (minSaturation>0) {
        std::vector<cv::Mat> v;
        cv::split(hsv,v);
        cv::threshold(v[1],mask,minSaturation,255,
                cv::THRESH_BINARY);
    }
    hranges[0]= 0.0;
    hranges[1]= 180.0;
    channels[0]= 0;

    cv::calcHist(&hsv,1 , channels, mask, hist, 1, histSize, ranges);

    return hist;

}
