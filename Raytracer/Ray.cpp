#include "Ray.hpp"


Ray::Ray()
{
}

Ray::Ray(Vector3 o, Vector3 d)
{
    origin = o;
    direction = d;
}

Ray::Ray(Vector3 o, Vector3 d, Hit h)
{
    origin = o;
    direction = d;
    hit = h;
}