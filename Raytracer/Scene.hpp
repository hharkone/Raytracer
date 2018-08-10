#pragma once
#include <vector>
#include <memory>

#include "Ray.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Viewport.hpp"


class Scene
{
public:
    Scene();
    ~Scene();

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
        { Vector3(-1e5 +  1.0, 40.8, 81.6)  , 1e5, Vector3(0.0) }, //Left wall
        { Vector3(1e5 + 99.0, 40.8, 81.6)   , 1e5, Vector3(1.0) }, //Right wall
        { Vector3(0.0,  0.0, -1e5)         , 1e5, Vector3(0.0) }, //Back wall
        { Vector3(50.0, -1e5, 81.6)         , 1e5, Vector3(0.5) }, //Floor
        { Vector3(50.0, 1e5 + 81.6, 81.6)   , 1e5, Vector3(1.0) }, //Ceiling
        { Vector3(27.0, 16.5, 47.0)         , 16.5, Vector3(1.0, 0.0, 0.0) }, //Left ball
        { Vector3(73.0, 16.5, 78.0)         , 16.5, Vector3(0.0, 1.0, 0.0) }, //Right ball
        { Vector3(50.0, 681.6 - .27,81.6)   , 600.0, Vector3(0.0) }, //Skylight
    };

    std::optional<Ray> intersect(size_t pixelX, size_t pixelY, double tmin, double tmax) const
    {
        Ray ray;
        ray.origin = camera->getPosition();
        ray.direction = [&]()
        {
            const double tf = std::tan(camera->getFOV() * 0.5);
            const double rpx = 2.0 * pixelX / viewport->getWidth() - 1.0;
            const double rpy = 2.0 * pixelY / viewport->getHeight() - 1.0;
            const Vector3 w = Vector3::normalize(Vector3(viewport->getAspect() * tf * rpx, tf * rpy, -1.0));

            return camera->getSide()*w.x + camera->getUp()*w.y + camera->getForward()*w.z;
        }();

        std::optional<Ray> minHit;
        for (const auto& sphere : spheres)
        {
            const auto h = sphere.intersect(ray, tmin, tmax);
            if (!h) { continue; }
            ray.hit = h->hit;
            tmax = ray.hit.distance;

            minHit = h;
        }
        if (minHit)
        {
            const auto* hitSphere = minHit->hit.sphere;
            minHit->hit.position = ray.origin + ray.direction * minHit->hit.distance;
            minHit->hit.normal = (minHit->hit.position - hitSphere->position) / hitSphere->radius;
        }

        ray.hit = minHit->hit;

        return ray;
    }
    
private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Viewport> viewport;
};

