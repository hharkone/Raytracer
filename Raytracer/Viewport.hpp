#pragma once
class Viewport
{
public:
    Viewport();
    Viewport(const int w, const int h);
    ~Viewport();

    void setWidth(const int w);
    void setHeight(const int h);
    int getWidth();
    int getHeight();
    double getAspect();

private:
    void calculateAspect();
    int width, height;
    double aspect;
};

