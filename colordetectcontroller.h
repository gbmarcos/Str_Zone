#ifndef COLORDETECTCONTROLLER_H
#define COLORDETECTCONTROLLER_H
#include "colordetector.h"

class ColorDetectController
{
public:
    ColorDetectController();
    int getColorDistanceThreshold() const;
    void setColorDistanceThreshold(int distance);
    void setTargetColor(unsigned char red,unsigned char green, unsigned char blue);
    void getTargetColor(unsigned char &red,unsigned char &green, unsigned char &blue) const;
    bool setInputImage(std::string filename);
    const cv::Mat getInputImage() const;
    void process();
    const cv::Mat getLastResult() const;
    ~ColorDetectController();
private:

    ColorDetector *cdetect;
    cv::Mat image;
    cv::Mat result;

};

#endif // COLORDETECTCONTROLLER_H
