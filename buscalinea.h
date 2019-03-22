#ifndef BUSCALINEA_H
#define BUSCALINEA_H
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
class BuscaLinea
{
public:
    BuscaLinea();
    void setAccResolution(double dRho, double dTheta);
    void setMinVote(int minv);
    void setLineLengthAndGap(double length, double gap);
    std::vector<cv::Vec4i> findLines(cv::Mat& binary);
    void drawDetectedLines(cv::Mat &image,cv::Scalar color=cv::Scalar(255,255,255));

private:
    cv::Mat img;
    std::vector<cv::Vec4i> lines;
    double deltaRho;
    double deltaTheta;
    int minVote;
    double minLength;
    double maxGap;
};

#endif // BUSCALINEA_H
