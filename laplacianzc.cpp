#include "laplacianzc.h"

LaplacianZC::LaplacianZC():aperture(3)
{
}

void LaplacianZC::setAperture(int a)
{
    aperture= a;
}

cv::Mat LaplacianZC::computeLaplacian(const cv::Mat &image)
{
    cv::Laplacian(image,laplace,CV_32F,aperture);
    img= image.clone();
    return laplace;
}

cv::Mat LaplacianZC::getLaplacianImage(double scale)
{
    if (scale<0) {
     double lapmin, lapmax;
     cv::minMaxLoc(laplace,&lapmin,&lapmax);
     scale= 127/ std::max(-lapmin,lapmax);
     }
     cv::Mat laplaceImage;
     laplace.convertTo(laplaceImage,CV_8U,scale,128);
     return laplaceImage;
}
