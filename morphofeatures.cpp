#include "morphofeatures.h"
#include <QDebug>

MorphoFeatures::MorphoFeatures():threshold(-1),
    cross(5,5,CV_8U,cv::Scalar(0)),
    diamond(5,5,CV_8U,cv::Scalar(1)),
    square(5,5,CV_8U,cv::Scalar(1)),
    x(5,5,CV_8U,cv::Scalar(0))
{
    for (int i=0; i<5; i++) {
        cross.at<uchar>(2,i)= 1;
        cross.at<uchar>(i,2)= 1;
    }

    diamond.at<uchar>(0,0)= 0;
    diamond.at<uchar>(0,1)= 0;
    diamond.at<uchar>(1,0)= 0;
    diamond.at<uchar>(4,4)= 0;
    diamond.at<uchar>(3,4)= 0;
    diamond.at<uchar>(4,3)= 0;
    diamond.at<uchar>(4,0)= 0;
    diamond.at<uchar>(4,1)= 0;
    diamond.at<uchar>(3,0)= 0;
    diamond.at<uchar>(0,4)= 0;
    diamond.at<uchar>(0,3)= 0;
    diamond.at<uchar>(1,4)= 0;

    for (int i=0; i<5; i++) {
        x.at<uchar>(i,i)= 1;
        x.at<uchar>(4-i,i)= 1;
    }

}

cv::Mat MorphoFeatures::getEdges(const cv::Mat &image)
{
    cv::Mat result;
    cv::morphologyEx(image,result,cv::MORPH_GRADIENT,cv::Mat());

    applyThreshold(result);
    return result;
}

void MorphoFeatures::applyThreshold(cv::Mat &result)
{
    if (threshold>0)
        cv::threshold(result, result,threshold, 255, cv::THRESH_BINARY_INV);

}

cv::Mat MorphoFeatures::getCorners(const cv::Mat &image)
{
    cv::Mat result;
    cv::dilate(image,result,cross);
    cv::erode(result,result,diamond);
    cv::Mat result2;
    cv::dilate(image,result2,x);
    cv::erode(result2,result2,square);
    cv::absdiff(result2,result,result);
    applyThreshold(result);
    return result;
}

void MorphoFeatures::drawOnImage(const cv::Mat &binary, cv::Mat &image)
{
    cv::Mat_<uchar>::const_iterator it= binary.begin<uchar>();
    cv::Mat_<uchar>::const_iterator itend= binary.end<uchar>();

        for (int i=0; it!= itend; ++it,++i) {
            if (!*it)
            {

                cv::circle(image,
                           cv::Point(i%image.step,i/image.step),
                           5,cv::Scalar(255,0,0));

            }
        }

}
int MorphoFeatures::getThreshold() const
{
    return threshold;
}

void MorphoFeatures::setThreshold(int value)
{
    threshold = value;
}



