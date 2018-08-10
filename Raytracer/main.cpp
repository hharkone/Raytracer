#include <vector>
#include <omp.h>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Viewport.hpp"
#include "Random.hpp"
#include "TgaWriter.hpp"

#define DEBUG_OUTPUT 0
#define DEBUG_NORMAL 0
#define DEBUG_DIFFUSE 0
#define DEBUG_EMISSION 1
#define DEBUG_VIEWDIRECTION 0

double packNormal(double v)
{
    return v * 0.5 + 0.5;
}

char doubleToColor(double v)
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

    #pragma omp parallel for schedule(dynamic, 1)
    for (size_t i = 0; i < pixels; i++)
    {
        thread_local Random rng(42 + omp_get_thread_num());
        const size_t x = i % w;
        const size_t y = h - i / w;

        double rnd = rng.next();

        TgaWriter::RGB_t pixel;
        const auto ray = scene.intersect(x, y, 0, 1e+10);
        if (ray->hit.sphere)
        {
            const auto d = ray->hit.sphere->diffuse;
            const auto e = ray->hit.sphere->emission;
            const auto n = ray->hit.normal;
            const auto v = ray->direction;

            const double dot = Vector3::dot(n, -v);

            pixel.red   = doubleToColor(d.x * dot);
            pixel.green = doubleToColor(d.y * dot);
            pixel.blue  = doubleToColor(d.z * dot);

#if defined(DEBUG_OUTPUT) && (DEBUG_OUTPUT != 0)

#if defined(DEBUG_NORMAL) && (DEBUG_NORMAL != 0)
        pixel.red = doubleToColor(packNormal(n.x));
        pixel.green = doubleToColor(packNormal(n.y));
        pixel.blue = doubleToColor(packNormal(n.z));
#endif // DEBUG_NORMAL

#if defined(DEBUG_REFLECTANCE) && (DEBUG_REFLECTANCE != 0)
        pixel.red = doubleToColor(r.x);
        pixel.green = doubleToColor(r.y);
        pixel.blue = doubleToColor(r.z);
#endif // DEBUG_REFLECTANCE

#if defined(DEBUG_EMISSION) && (DEBUG_EMISSION != 0)
        pixel.red = doubleToColor(e.x);
        pixel.green = doubleToColor(e.y);
        pixel.blue = doubleToColor(e.z);
#endif // DEBUG_EMISSION

#if defined(DEBUG_VIEWDIRECTION) && (DEBUG_VIEWDIRECTION != 0)
        pixel.red = doubleToColor(packNormal(v.x));
        pixel.green = doubleToColor(packNormal(v.y));
        pixel.blue = doubleToColor(packNormal(v.z));
#endif // DEBUG_VIEWDIRECTION

#endif // DEBUG_OUTPUT

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