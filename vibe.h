#ifndef VIBE_H
#define VIBE_H
#include "opencv2/core/core.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "opencv2/core/types_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

class Vibe
{
private:
    int width;
        int height;
        int nbSamples;
        int reqMatches;
        int radius;
        int bogo_radius;
        int subsamplingFactor;
        RNG rng;
        vector< Mat_<uchar> > samples;
            Mat_<uchar> segmentation;

public:
    Vibe(int w, int h, int nbSamples=20, int reqMatches=2, int radius=400, int subsamplingFactor=8);
    void clear();
    void segment(const Mat & img, Mat & segmentationMap);


};

#endif // VIBE_H
