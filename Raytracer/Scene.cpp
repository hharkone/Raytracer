#include "Scene.hpp"


void Scene::setCamera(std::shared_ptr<Camera> c)
{
    camera = c;
}

std::shared_ptr<Camera> Scene::getCamera()
{
    return camera;
}

void Scene::setViewport(std::shared_ptr<Viewport> c)
{
    viewport = c;
}

std::shared_ptr<Viewport> Scene::getViewport()
{
    return viewport;
}
