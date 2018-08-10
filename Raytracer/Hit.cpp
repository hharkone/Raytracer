#include "Hit.hpp"

Hit::Hit()
{
}

Hit::Hit(double d, Vector3 p, Vector3 n, const Sphere* s)
{
    distance = d;
    position = p;
    normal = n;
    sphere = s;
}
