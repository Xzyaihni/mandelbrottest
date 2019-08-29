#include <bitmap_image.hpp>
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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

            real2 = real*real;
            imag2 = imag*imag;

            if((real==ckr)&&(imag==cki))
            {
                return color*2;
            }

            if(sqrt(real2+imag2)>10000)
            {
                double V = log(sqrt(real2+imag2))/(1<<p);
                color = log(V)/R;
                return color;
            }

        }
    }
    while(ptot!=iterations);
    return color*2;
}

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

int displayWindow(double xbD, double ybD, double zoomD)
{
    sf::RenderWindow window(sf::VideoMode(500,500),"Mandelbrot viewer");

    sf::Texture texture;
    texture.loadFromFile("mandelbrot.bmp");

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,500,500));

    double f500 = 500.0f;
    double f05 = 0.5f;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                xbD += (position.x/f500-f05)*zoomD;
                ybD += (position.y/f500-f05)*zoomD;
                zoomD /= 2;
                cout << xbD << endl;
                cout << ybD << endl;
                cout << zoomD << endl;
                drawMandelbrot(500,500,1000,xbD,ybD,zoomD);
                texture.loadFromFile("mandelbrot.bmp");
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

int main()
{
    unsigned int width,height,iterations;
    double xb,yb,zoom;
    width = 500;
    height = 500;
    iterations = 10000;

    xb = -1;
    yb = 0;
    zoom = 3;

    drawMandelbrot(width,height,iterations,xb,yb,zoom);

    return displayWindow(xb,yb,zoom);
}
