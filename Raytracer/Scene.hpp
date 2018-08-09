#pragma once
#include <vector>
#include "Sphere.hpp"

class Scene
{
public:
    Scene();
    ~Scene();

    std::vector<Sphere> spheres
    {
        { Vector3(-0.5, 0.0, 0.0), 0.5 },
        { Vector3( 0.5, 0.0, 0.0), 0.5 },
    };

    std::optional<Sphere::Hit> intersect(const Ray& ray, double tmin, double tmax) const
    {
        std::optional<Sphere::Hit> minh;
        for (const auto& sphere : spheres)
        {
            const auto h = sphere.intersect(ray, tmin, tmax);
            if (!h) { continue; }
            minh = h;
            tmax = minh->t;
        }
        if (minh)
        {
            const auto* s = minh->sphere;
            minh->position = ray.origin + ray.direction * minh->t;
            minh->normal = (minh->position - s->position) / s->radius;
        }
        return minh;
    }
    
};

