#include "colordetectcontroller.h"

ColorDetectController::ColorDetectController()
{
    cdetect= new ColorDetector();
}
void ColorDetectController::setColorDistanceThreshold(int distance){

    cdetect->setColorDistanceThreshold(distance);

}


void ColorDetectController::setTargetColor(unsigned char red,unsigned char green, unsigned char blue){

    cdetect->setTargetColor(red,green,blue);

}

int ColorDetectController::getColorDistanceThreshold() const{

    return cdetect->getColorDistanceThreshold();

}

void ColorDetectController::getTargetColor(unsigned char &red,unsigned char &green, unsigned char &blue) const{

    cv::Vec3b color= cdetect->getTargetColor();
    red= color[2];
    green= color[1];
    blue= color[0];

}

bool ColorDetectController::setInputImage(std::string filename){

    image= cv::imread(filename);
    if (!image.data)
        return false;
    else
        return true;

}

const cv::Mat ColorDetectController::getInputImage() const{

    return image;

}

const cv::Mat ColorDetectController::getLastResult() const{

    return result;

}

void ColorDetectController::process(){

    result= cdetect->process(image);

}

ColorDetectController::~ColorDetectController() {

    delete cdetect;

}


