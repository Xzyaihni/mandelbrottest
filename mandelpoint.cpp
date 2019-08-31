#include <math.h>
#include "mandelpoint.h"

using namespace std;

double point(double x, double y, unsigned int iterations, double R)
{
    double color = 1;

    double ckr, cki;

    double real = 0;
    double imag = 0;

    double real2 = 0;
    double imag2 = 0;

    unsigned int p = 0, ptot = 8;

    do
    {
        ckr = real;
        cki = imag;

        ptot+=ptot;
        if(ptot>iterations)
        {
            ptot = iterations;
        }

        for(;p<ptot;p++)
        {

            imag = 2*real*imag+y;
            real = real2-imag2+x;

            if((real==ckr)&&(imag==cki))
            {
                return 0;
            }

            real2 = real*real;
            imag2 = imag*imag;

            if(sqrt(real2+imag2)>100)
            {
                double V = log(sqrt(real2+imag2))/pow(2,p);
                color = log(V)/R;
                return color;
            }

        }
    }
    while(ptot!=iterations);
    return 0;
}
