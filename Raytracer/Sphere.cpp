#include "Sphere.hpp"


Sphere::Sphere()
{
}

Sphere::Sphere(Vector3 p, double r, Vector3 reflect)
{
    position = p;
    radius = r;
    reflectance = reflect;
}