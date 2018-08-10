#include <vector>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Viewport.hpp"
#include "TgaWriter.hpp"

double packNormal(double v)
{
    return v * 0.5 + 0.5;
}

int doubleToColor(double v)
{
    return std::min(std::max(int(v * 255), 0), 255);
};

int tonemap(double v)
{
    return std::min(std::max(int(std::pow(v, 1 / 2.2) * 255), 0), 255);
};

int main()
{
    // Image size
    const size_t w = 1200;
    const size_t h = 800;
    const size_t pixels = w * h;

    std::vector<TgaWriter::RGB_t>* byteArray = new std::vector<TgaWriter::RGB_t>(pixels);

    Viewport* viewport = new Viewport(w, h);
    Scene scene;

    Vector3 cameraPos = Vector3(50.0, 52.0, 295.6);
    Vector3 cameraIntrest = cameraPos + Vector3(0.0, -0.042612, -1.0);
    double cameraFov = 30.0;
    Camera* camera = new Camera(cameraPos, cameraIntrest, cameraFov);

    scene.setCamera(std::shared_ptr<Camera>(camera));
    scene.setViewport(std::shared_ptr<Viewport>(viewport));

    for (size_t i = 0; i < pixels; i++)
    {
        const size_t x = i % w;
        const size_t y = h - i / w;

        TgaWriter::RGB_t pixel;
        const auto ray = scene.intersect(x, y, 0, 1e+10);
        if (ray)
        {
            const auto r = ray->hit.sphere->reflectance;
            const auto n = ray->hit.normal;
            const double dot = Vector3::dot(n, ray->direction);

            pixel.red   = doubleToColor(packNormal(n.x));
            pixel.green = doubleToColor(packNormal(n.y));
            pixel.blue  = doubleToColor(packNormal(n.z));
        }
        else
        {
            pixel.red = pixel.green = pixel.blue = 0;
        }

        byteArray->at(i) = pixel;
    }

    TgaWriter::WriteTGA("result.tga", byteArray, w, h);

    return 0;
}