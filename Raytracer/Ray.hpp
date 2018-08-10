#pragma once
#include "Vector3.hpp"
#include "Hit.hpp"


struct Ray
{
    Vector3 origin;
    Vector3 direction;
    Hit hit;

    Ray();
    Ray(Vector3 o, Vector3 d);
    Ray(Vector3 o, Vector3 d, Hit h);
};
