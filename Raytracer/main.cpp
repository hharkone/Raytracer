#include <iostream>
#include <fstream>
#include <vector>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Scene.hpp"


double unpack(double v)
{
    return v * 0.5 + 0.5;
}

int doubleToColor(double v)
{
    return std::min(std::max(int(v * 255), 0), 255);
};

int main()
{
    // Image size
    const int w = 1200;
    const int h = 800;

    std::ofstream ofs("result.ppm");
    ofs << "P3\n" << w << " " << h << "\n255\n";

    Scene scene;

    for (int i = 0; i < w * h; i++)
    {
        const int x = i % w;
        const int y = i / w;

        Ray ray;

        ray.origin = Vector3(2.0 * double(x) / w - 1.0, 2.0 * double(y) / h - 1.0, 5.0);
        ray.direction = Vector3(0.0, 0.0, -1.0);

        const auto hit = scene.intersect(ray, 0, 1e+10);
        if (hit)
        {
            const auto n = hit->normal;

            ofs << doubleToColor(unpack(n.x)) << " "
                << doubleToColor(unpack(n.y)) << " "
                << doubleToColor(unpack(n.z)) << "\n";
        }
        else
        {
            ofs << "0 0 0\n";
        }

        
    }

    return 0;
}