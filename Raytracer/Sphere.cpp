#include "Sphere.hpp"


Sphere::Sphere()
{
}

Sphere::Sphere(Vector3 p, double r, Vector3 diff)
{
    position = p;
    radius = r;
    diffuse = diff;
    emission = Vector3();
}

Sphere::Sphere(Vector3 p, double r, Vector3 diff, Vector3 emitt)
{
    position = p;
    radius = r;
    diffuse = diff;
    emission = emitt;
}