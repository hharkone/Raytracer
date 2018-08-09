#pragma once
#include <optional>
#include "Vector3.hpp"
#include "Ray.hpp"

class Sphere
{
public:
    Sphere();
    Sphere(Vector3 p, double r);
    ~Sphere();

    struct Hit
    {
        double t;
        Vector3 position;
        Vector3 normal;
        const Sphere* sphere;
    };

    double radius;
    Vector3 position;
    //Vector3 R;
    //Vector3 Le;

    std::optional<Sphere::Hit> Sphere::intersect(const Ray& ray, double tmin, double tmax) const
    {
        const Vector3 op = position - ray.origin;
        const double b = Vector3::dot(op, ray.direction);
        const double det = b * b - Vector3::dot(op, op) + radius * radius;
        if (det < 0) { return {}; }

        const double t1 = b - sqrt(det);
        if (tmin < t1 && t1 < tmax) { return Hit{ t1,{},{}, this }; }

        const double t2 = b + sqrt(det);
        if (tmin < t2 && t2 < tmax) { return Hit{ t2,{},{}, this }; }

        return {};
    }

private:

};

