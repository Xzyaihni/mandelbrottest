#include <cmath>
#include <complex>
#include "mandelpoint.h"

double point(double x, double y, unsigned int iterations, double R)//, double lightDirR, double lightDirI)
{
    double color = 1;
	float lHeight = 1.5;

    double ckr, cki;

    double real = 0;
    double imag = 0;

    double real2 = 0;
    double imag2 = 0;
	
	//double tempDer;
	//double derR = 1;
	//double derI = 0;

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

			//tempDer = 2*derR*real-2*derI*imag+1;
			//derI = 2*derR*imag+2*derI*real;
			//derR = tempDer;

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
				
				//std::complex<double> u = std::complex<double>(real,imag)/std::complex<double>(derR,derI);
				//
				//u = u/std::abs(u);
				//
				//double normal_shading = u.real()*lightDirR-u.imag()*lightDirI+lHeight;
				//
				//normal_shading = normal_shading/(1+lHeight);
				//normal_shading = normal_shading < 0 ? 0 : normal_shading;
				
                return color;//*normal_shading;
            }

        }
    }
    while(ptot!=iterations);
    return 0;
}
