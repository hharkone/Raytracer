#pragma once
#include <vector>
#include <memory>
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
        { Vector3(-0.5, 0.0, 0.0), 0.5 },
        { Vector3( 0.5, 0.0, 0.0), 0.5 },
    };

    std::optional<Sphere::Hit> intersect(int pixelX, int pixelY, double tmin, double tmax) const
    {
        Ray ray;
        ray.origin = camera->getPosition();
        ray.direction = [&]()
        {
            const double tf = std::tan(camera->getFOV() * 0.5);
            const double rpx = 2.0 * pixelX / viewport->getWidth() - 1;
            const double rpy = 2.0 * pixelY / viewport->getHeight() - 1;
            const Vector3 w = Vector3::normalize(Vector3(viewport->getAspect() * tf * rpx, tf * rpy, -1.0));

            return camera->side*w.x + camera->up*w.y + camera->forward*w.z;
        }();

        std::optional<Sphere::Hit> minHit;
        for (const auto& sphere : spheres)
        {
            const auto h = sphere.intersect(ray, tmin, tmax);
            if (!h) { continue; }
            minHit = h;
            tmax = minHit->distance;
        }
        if (minHit)
        {
            const auto* hitSphere = minHit->sphere;
            minHit->position = ray.origin + ray.direction * minHit->distance;
            minHit->normal = (minHit->position - hitSphere->position) / hitSphere->radius;
        }
        return minHit;
    }
    
private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Viewport> viewport;
};

