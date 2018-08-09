#pragma once
#include "Vector3.hpp"

class Ray
{
public:

    Vector3 origin;
    Vector3 direction;

    Ray(void);
    Ray(Vector3 o, Vector3 d);

    ~Ray();
};
