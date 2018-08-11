#pragma once
#include <vector>
#include <memory>

#include "Ray.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Random.hpp"
#include "Viewport.hpp"


class Scene
{
public:

    void setCamera(std::shared_ptr<Camera> c);
    std::shared_ptr<Camera> getCamera();

    void setViewport(std::shared_ptr<Viewport> c);
    std::shared_ptr<Viewport> getViewport();


    std::vector<Sphere> spheres
    {
        //1 Two test spheres
        //{ Vector3(-0.5, 0.0, 0.0), 1.0, Vector3(0.0) },
        //{ Vector3(0.0, 0.0, -10001.0), 10000.0, Vector3(0.0) },
        //{ Vector3( 0.5, 0.0, 0.0), 1.0 },

        //Cornell box
        { Vector3(-1e5 +  1.0, 40.8, 81.6)  , 1e5, Vector3(0.75, 0.25, 0.25) }, //Left wall
        { Vector3(1e5 + 99.0, 40.8, 81.6)   , 1e5, Vector3(0.25, 0.25, 0.75) }, //Right wall
        { Vector3(0.0,  0.0, -1e5)          , 1e5, Vector3(0.75) }, //Back wall
        { Vector3(50.0, -1e5, 81.6)         , 1e5, Vector3(0.75) }, //Floor
        { Vector3(50.0, 1e5 + 81.6, 81.6)   , 1e5, Vector3(0.75) }, //Ceiling
        { Vector3(27.0, 16.5, 47.0)         , 16.5, Vector3(0.7) }, //Left ball
        { Vector3(73.0, 16.5, 78.0)         , 16.5, Vector3(0.7) }, //Right ball
        { Vector3(50.0, 681.6 - .27,81.6)   , 600.0, Vector3(), Vector3(12.0) }, //Skylight
    };

    std::optional<Ray> intersect(const Ray& ray, double tmin, double tmax, Random& rng) const
    {
        std::optional<Ray> minHit;
        for (const auto& sphere : spheres)
        {
            const auto h = sphere.intersect(ray, tmin, tmax);
            if (!h) { continue; }

            minHit->hit = h->hit;
            tmax = minHit->hit.distance;

            //ray.hit = h->hit;
            //tmax = ray.hit.distance;

            minHit = h;
        }
        if (minHit)
        {
            const auto* hitSphere = minHit->hit.sphere;
            minHit->hit.position = ray.origin + ray.direction * minHit->hit.distance;
            minHit->hit.normal = (minHit->hit.position - hitSphere->position) / hitSphere->radius;
        }

        minHit->origin = minHit->hit.position;

        return minHit;
    }
    
private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Viewport> viewport;
};

