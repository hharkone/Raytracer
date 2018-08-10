#pragma once
#include "Vector3.hpp"

class Sphere;

struct Hit
{
    double distance;
    Vector3 position;
    Vector3 normal;
    const Sphere* sphere;

    Hit();
    Hit(double d, Vector3 p, Vector3 n, const Sphere* s);
};