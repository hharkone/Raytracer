#pragma once
#include <optional>
#include "Vector3.hpp"
#include "Ray.hpp"

class Primitive
{
public:
    Primitive();
    ~Primitive();

    virtual struct Hit
    {
        double t;
        Vector3 p;
        Vector3 n;
        const Primitive* primitive;
    };

    Vector3 position;

    void setPosition(Vector3 v);
    Vector3 getPosition();

    virtual std::optional<Hit> intersect(const Ray& ray, double tmin, double tmax);

private:

};

