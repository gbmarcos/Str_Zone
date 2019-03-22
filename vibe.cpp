#include "vibe.h"
#include "opencv2/core/core.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "opencv2/core/types_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

Vibe::Vibe(int w, int h, int nbSamples, int reqMatches, int radius, int subsamplingFactor): width(w)
  , height(h)
  , nbSamples(nbSamples)
  , reqMatches(reqMatches)
  , radius(radius)
  , bogo_radius(200000)
  , subsamplingFactor(subsamplingFactor)
  , rng(getTickCount())
  , segmentation(height,width)
{
  clear();
}

void Vibe::clear()
{
    samples.clear();
            for ( int i=0; i<nbSamples; i++ )
                samples.push_back( Mat_<uchar>(height,width,8) );
            bogo_radius= 200000;
}

void Vibe::segment(const Mat &img, Mat &segmentationMap)
{
    if ( nbSamples != samples.size() )
                clear();

            bogo_radius = bogo_radius > radius
                        ? bogo_radius *= 0.7
                        : radius;

            Mat_<uchar> image(img);
            for (int x=1; x<width-1; x++) // spare a 1 pixel border for the neighbour sampling
            {
                for (int y=1; y<height-1; y++)
                {
                    uchar pixel = image(y,x);

                    // comparison with the model
                    int count = 0;
                    for ( int i=0; (i<nbSamples)&&(count<reqMatches); i++ )
                    {
                        int distance = (pixel - samples[i](y,x));
                        count += (distance*distance < bogo_radius);
                    }
                    // pixel classification according to reqMatches
                    if (count >= reqMatches) // the pixel belongs to the background
                    {
                        // store 'bg' in the segmentation map
                        segmentation(y,x) = 0;
                        // gets a random number between 0 and subsamplingFactor-1
                        int randomNumber = rng.uniform(0, subsamplingFactor);
                        // update of the current pixel model
                        if (randomNumber == 0) // random subsampling
                        {
                            // other random values are ignored
                            randomNumber = rng.uniform(0, nbSamples);
                            samples[randomNumber](y,x) = pixel;
                        }
                        // update of a neighboring pixel model
                        randomNumber = rng.uniform(0, subsamplingFactor);
                        if (randomNumber == 0) // random subsampling
                        {
                            // chooses a neighboring pixel randomly
                            const static int nb[8][2] = {-1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1, -1,-1};
                            int n = rng.uniform(0,8);
                            int neighborX = x + nb[n][1], neighborY = y + nb[n][0];
                            // chooses the value to be replaced randomly
                            randomNumber = rng.uniform(0, nbSamples);
                            samples[randomNumber](neighborY,neighborX) = pixel;
                        }
                    }
                    else // the pixel belongs to the foreground
                    {    // store 'fg' in the segmentation map
                        segmentation(y,x) = 255;
                    }
                }
            }
            segmentationMap = segmentation;
        }

