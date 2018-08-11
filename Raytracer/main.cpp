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

#define SAMPLES_PER_PIXEL 10
#define SAMPLES_DEPTH 2

double packFloat(double v)
{
    return v * 0.5 + 0.5;
}

Vector3 packNormal(Vector3 v)
{
    return Vector3(packFloat(v.x), packFloat(v.y), packFloat(v.z));
}
/*
unsigned char doubleToByte(double v)
{
    return std::min(std::max(int(v * 255), 0), 255);
}

TgaWriter::RGB_t vectorToColor(Vector3 v)
{
    TgaWriter::RGB_t out{ doubleToByte(v.x), doubleToByte(v.y), doubleToByte(v.z) };
    return out;
};
*/
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

    std::vector<Vector3> I(pixels);
    #pragma omp parallel for schedule(dynamic, 1)
    for (size_t i = 0; i < pixels; i++)
    {
        thread_local Random rng(42 + omp_get_thread_num());
        const size_t x = i % w;
        const size_t y = i / w;

        Vector3 floatPixel(0.0, 0.0, 0.0);

        for (int j = 0; j < SAMPLES_PER_PIXEL; j++)
        {
            //Construct initial ray from camera
            Ray ray;
            ray.origin = camera->getPosition();
            ray.direction = [&]()
            {
                const double tf = std::tan(camera->getFOV() * 0.5);
                const double rpx = 2.0 * (x + rng.next()) / viewport->getWidth() - 1.0;
                const double rpy = 2.0 * (y + rng.next()) / viewport->getHeight() - 1.0;
                const Vector3 w = Vector3::normalize(Vector3(viewport->getAspect() * tf * rpx, tf * rpy, -1.0));

                return camera->getSide()*w.x + camera->getUp()*w.y + camera->getForward()*w.z;
            }();

            //Bounce
            Vector3 sampleColor(0.0), traceEnergy(1.0);
            for (int depth = 0; depth < SAMPLES_DEPTH; depth++)
            {
                // Intersection
                const auto trace = scene.intersect(ray, 1e-4, 1e+10, rng);
                if (!trace->hit.sphere)
                {
                    break;
                }
                // Add contribution
                sampleColor = sampleColor + traceEnergy * trace->hit.sphere->emission;
                // Update next direction
                ray.origin = trace->origin;
                ray.direction = [&]()
                {
                    // Sample direction in local coordinates
                    const auto n = Vector3::dot(trace->hit.normal, -ray.direction) > 0 ? trace->hit.normal : -trace->hit.normal;
                    const auto& t = Vector3::tangentSpace(n);
                    //const auto& [u, v] = Vector3::tangentSpace(n);

                    const auto d = [&]()
                    {
                        const double r = sqrt(rng.next());
                        const double t = 2.0 * PI * rng.next();
                        const double x = r * cos(t);
                        const double y = r * sin(t);
                        return Vector3(x, y, sqrt(std::max(.0,1.0-x*x-y*y)));
                    }();
                    // Convert to world coordinates
                    return std::get<0>(t) * d.x + std::get<1>(t) * d.y + n * d.z;
                }();
                // Update throughput
                traceEnergy = traceEnergy * trace->hit.sphere->diffuse;
                if (std::max({ traceEnergy.x, traceEnergy.y, traceEnergy.z }) == 0)
                {
                    //If trace has no contribution we can stop
                    break;
                }
            }

#if defined(DEBUG_OUTPUT) && (DEBUG_OUTPUT != 0)

#if defined(DEBUG_NORMAL) && (DEBUG_NORMAL != 0)
                floatPixel = packNormal(n);
#endif // DEBUG_NORMAL

#if defined(DEBUG_REFLECTANCE) && (DEBUG_REFLECTANCE != 0)
                floatPixel = r;
#endif // DEBUG_REFLECTANCE

#if defined(DEBUG_EMISSION) && (DEBUG_EMISSION != 0)
                floatPixel = e;
#endif // DEBUG_EMISSION

#if defined(DEBUG_VIEWDIRECTION) && (DEBUG_VIEWDIRECTION != 0)
                floatPixel = packNormal(v);
#endif // DEBUG_VIEWDIRECTION

#else // DEBUG_OUTPUT

                //Add sample
            I[i] = I[i] + sampleColor / SAMPLES_PER_PIXEL;

#endif
        }

        //I[i] = floatPixel;
    }

    TgaWriter::WriteTGA("result.tga", I, w, h);

    return 0;
}