#include "bitmap_image.hpp"
#include <math.h>
#include "mandelimg.h"
#include "mandelpoint.h"

using namespace std;

void drawMandelbrot(unsigned int width, unsigned int height, unsigned int iterations,
                    double xb, double yb, double zoom)
{
        bitmap_image image(width,height);

    double dc = zoom/((double)max(width,height)-1);

    double R = M_LN2;

    double red = 1/R;
    double green = (1/(3*sqrt(2)))/R;
    double blue = (1/(7*pow(3,0.125f)))/R;

    #pragma omp parallel for collapse(2)
    for(unsigned int y = 0; y < height; y++)
    {
        for(unsigned int x = 0; x < width; x++)
        {
            double result = point(xb+dc*(x-(double)width/2),yb+dc*(y-(double)height/2),iterations,R);
            image.set_pixel(x,y,(1-cos(red*result))/2*255,
                            (1-cos(green*result))/2*255,
                            (1-cos(blue*result))/2*255);
        }
    }

    image.save_image("mandelbrot.bmp");
}
