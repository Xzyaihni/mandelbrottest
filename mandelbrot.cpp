#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "mandelimg.h"

using namespace std;

int displayWindow(double xbD, double ybD, double zoomD, unsigned int width, unsigned int height, unsigned int iterations)
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

    return displayWindow(xb,yb,zoom,width,height,iterations);
}
