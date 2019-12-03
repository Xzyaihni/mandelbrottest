#include "bitmap_image.hpp"
#include <cmath>
#include "mandelimg.h"
#include "mandelpoint.h"

using namespace std;

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}

void drawMandelbrot(unsigned int width, unsigned int height, unsigned int iterations,
                    double xb, double yb, double zoom)
{
        bitmap_image image(width,height);

    double dc = zoom/((double)max(width,height)-1);

    double R = M_LN2;

	HsvColor col;
    col.h = round(1/R * 255);
    col.s = round((1/(3*M_SQRT2))/R * 255);
    col.v = round((1/(7*pow(3,1./8.)))/R * 255);
	
	RgbColor newCol = HsvToRgb(col);

    #pragma omp parallel for collapse(2)
    for(unsigned int y = 0; y < height; y++)
    {
        for(unsigned int x = 0; x < width; x++)
        {
            double result = point(xb+dc*(x-(double)width/2),yb+dc*(y-(double)height/2),iterations,R);
            image.set_pixel(x,y,(1-cos((float)newCol.r/255*result))*127.5f,
                            (1-cos((float)newCol.g/255*result))*127.5f,
                            (1-cos((float)newCol.b/255*result))*127.5f);
        }
    }

    image.save_image("mandelbrot.bmp");
}
