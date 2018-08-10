#pragma once
#include <optional>

#include "Vector3.hpp"
#include "Ray.hpp"


class Sphere
{
public:
    Sphere();
    Sphere(Vector3 p, double r, Vector3 diff, Vector3 emitt);


    double radius;
    Vector3 position;
    Vector3 diffuse;
    Vector3 emission;

    std::optional<Ray> Sphere::intersect(Ray& ray, double tmin, double tmax) const
    {
        const Vector3 op = position - ray.origin;
        const double b = Vector3::dot(op, ray.direction);
        const double det = b * b - Vector3::dot(op, op) + radius * radius;
        if (det < 0) { return {}; }

        const double t1 = b - sqrt(det);
        if (tmin < t1 && t1 < tmax) { ray.hit = { t1,{},{}, this }; return ray; }

        const double t2 = b + sqrt(det);
        if (tmin < t2 && t2 < tmax) { ray.hit = { t2,{},{}, this }; return ray; }

        return {};
    }

private:

};

