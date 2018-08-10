#include "Camera.hpp"


Camera::Camera()
{
    setFOV(50.0);
    setPosition(Vector3(0.0, 0.0, -1.0));
    setPointOfIntrest(Vector3(0.0, 0.0, 0.0));

    updateBasisVectors();
}

Camera::Camera(Vector3 pos, Vector3 pointofintrest, double fov)
{
    setFOV(fov);
    setPosition(pos);
    setPointOfIntrest(pointofintrest);
}

Camera::~Camera()
{
}

void Camera::updateBasisVectors()
{
    //Basis vectors
    forward = Vector3::normalize(position - pointOfIntrest);
    side = Vector3::normalize(Vector3::cross(worldUp, forward));
    up = Vector3::cross(forward, side);
}

void Camera::setFOV(double deg)
{
    fov = deg * PI / 180.0;
}

void Camera::setPosition(Vector3& pos)
{
    position = pos;
    updateBasisVectors();
}

void Camera::setPointOfIntrest(Vector3& pos)
{
    pointOfIntrest = pos;
    updateBasisVectors();
}

double Camera::getFOV()
{
    return fov / PI * 180.0;
}

Vector3 Camera::getPosition()
{
    return position;
}

Vector3 Camera::getPointOfIntrest()
{
    return pointOfIntrest;
}
