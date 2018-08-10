#include <memory>
#include "Viewport.hpp"


Viewport::Viewport()
{
    width = 0;
    height = 0;
    aspect = 0.0;
}

Viewport::Viewport(const int w, const int h)
{
    width = w;
    height = h;
    calculateAspect();
}

Viewport::~Viewport()
{
}

void Viewport::calculateAspect()
{
    aspect = double(width) / double(height);
}

void Viewport::setWidth(const int w)
{
    width = w;
}

void Viewport::setHeight(const int h)
{
    height = h;
}

int Viewport::getWidth()
{
    return width;
}

int Viewport::getHeight()
{
    return height;
}

double Viewport::getAspect()
{
    return aspect;
}
