#include "Primitive.hpp"

Primitive::Primitive()
{
}

Primitive::~Primitive()
{
}

void Primitive::setPosition(Vector3 v)
{
    position = v;
}

Vector3 Primitive::getPosition()
{
    return position;
}

std::optional <Primitive::Hit> Primitive::intersect(const Ray & ray, double tmin, double tmax)
{
    return {};
}
