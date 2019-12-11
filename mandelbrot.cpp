#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "mandelimg.h"
#include <iomanip>
#include <sstream>

using namespace std;

int displayWindow(__float128 xbD, __float128 ybD, __float128 zoomD, unsigned int width, unsigned int height, unsigned int iterations)
{
    sf::RenderWindow window(sf::VideoMode(width,height),"Mandelbrot viewer");

    sf::Texture texture;
    texture.loadFromFile("mandelbrot.bmp");

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,width,height));

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
                xbD += (position.x/(__float128)width-0.5)*zoomD;
                ybD += (position.y/(__float128)height-0.5)*zoomD;
                zoomD /= 2;
                cout << (long double)xbD << endl;
                cout << (long double)ybD << endl;
                cout << (long double)zoomD << endl;
                drawMandelbrot(width,height,iterations,xbD,ybD,zoomD);
                texture.loadFromFile("mandelbrot.bmp");
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

template <class setType>
setType SetArg(string tooltip)
{
    setType arg;

    stringstream ss;
    ss.clear();
    ss.str("");
    string input = "";

    cout << endl << tooltip << endl;

    getline(cin,input);
    ss.str(input);

    ss >> arg;

    ss.clear();
    ss.str("");
    input.clear();

    return arg;
}

int main()
{
    unsigned int width,height,iterations;
    __float128 xb,yb,zoom;

    bool interactive;

    /*
    width = 500;
    height = 500;
    iterations = 10000;

    xb = -1;
    yb = 0;
    zoom = 3;
    */

    width = SetArg<unsigned int>("image width: ");
    height = SetArg<unsigned int>("image height: ");

    iterations = SetArg<unsigned int>("iterations per pixel: ");

    xb = SetArg<long double>("x offset: ");
    yb = SetArg<long double>("y offset: ");

    zoom = SetArg<long double>("zoom: ");

    interactive = SetArg<bool>("0 if you want to write image to file and quit, 1 if you want to continue generating: ");

    drawMandelbrot(width,height,iterations,xb,yb,zoom);

    if(interactive)
    {
        cout << fixed << setprecision(64);
        return displayWindow(xb,yb,zoom,width,height,iterations);
    } else
    {
        return 5;
    }
}
