#ifndef MORPHOFEATURES_H
#define MORPHOFEATURES_H

#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
class MorphoFeatures
{
public:
    MorphoFeatures();
    cv::Mat getEdges(const cv::Mat &image);
    void applyThreshold(cv::Mat& result);
    cv::Mat getCorners(const cv::Mat &image);
    void drawOnImage(const cv::Mat& binary, cv::Mat& image);

    int getThreshold() const;
    void setThreshold(int value);

private:
    int threshold;
    cv::Mat cross;
    cv::Mat diamond;
    cv::Mat square;
    cv::Mat x;
};

#endif // MORPHOFEATURES_H
