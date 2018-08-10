#pragma once
#define PI 3.141592
#include "Vector3.hpp"
class Camera
{
public:
    Camera();
    Camera(Vector3 pos, Vector3 pointofintrest, double fov);
    ~Camera();

    //Basis vectors
    Vector3 forward;
    Vector3 side;
    Vector3 up;

    void updateBasisVectors();
    void setFOV(double f);
    void setPosition(Vector3& pos);
    void setPointOfIntrest(Vector3& pos);

    double getFOV();
    Vector3 getPosition();
    Vector3 getPointOfIntrest();

private:
    Vector3 position;
    Vector3 pointOfIntrest;
    double fov = 50.0 * PI / 180.0;
    const Vector3 worldUp = Vector3(0.0, 1.0, 0.0);
};

