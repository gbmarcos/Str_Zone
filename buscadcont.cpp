#include "buscadcont.h"

BuscadCont::BuscadCont(): threshold(-1.0f)
{
    ranges[0]= hranges;
    ranges[1]= hranges;
    ranges[2]= hranges;
}

void BuscadCont::setThreshold(double t){

    threshold= t;
}

double BuscadCont::getThreshold(){

    return threshold;
}

void BuscadCont::setHistogram(const cv::MatND& h){

    histogram= h;
    cv::normalize(histogram,histogram,1.0);
}

cv::Mat BuscadCont::find(const cv::Mat& image,float minValue,float maxValue, int dim){

    cv::Mat result;
    hranges[0]= minValue;
    hranges[1]= maxValue;
    for (int i=0; i<dim; i++)
        this->channels[i]= i;

    cv::calcBackProject(&image, 1,this->channels,histogram,result,ranges,255.0);


    if (threshold>0.0)
        cv::threshold(result, result,55*threshold, 255, cv::THRESH_BINARY);
    return result;
}
