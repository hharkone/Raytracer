#include "Ray.hpp"

Ray::Ray(void)
{
}

Ray::Ray(Vector3 o, Vector3 d)
{
    origin = o;
    direction = d;
}

Ray::~Ray()
{
}
