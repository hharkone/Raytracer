#include "Vector3.hpp"

Vector3::~Vector3(){}

Vector3 Vector3::operator+(Vector3& a)
{
    return Vector3(x + a.x, y + a.y, z + a.z);
}

const Vector3 Vector3::operator+(const Vector3 & a) const
{
    return Vector3(x + a.x, y + a.y, z + a.z);
}



Vector3 Vector3::operator-(Vector3& a)
{
    return Vector3(x - a.x, y - a.y, z - a.z);
}

const Vector3 Vector3::operator-(const Vector3 & a) const
{
    return Vector3(x - a.x, y - a.y, z - a.z);
}



Vector3 Vector3::operator*(Vector3& a)
{
    return Vector3(x * a.x, y * a.y, z * a.z);
}

Vector3 Vector3::operator/(Vector3& a)
{
    return Vector3(x / a.x, y / a.y, z / a.z);
}

Vector3 Vector3::operator-(const double scalar)
{
    return Vector3(x - scalar, y - scalar, z - scalar);
}




Vector3 Vector3::operator*(double scalar)
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

const Vector3 Vector3::operator*(double scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}




Vector3 Vector3::operator/(double scalar)
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}
const Vector3 Vector3::operator/(const double scalar) const
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}




double Vector3::dot(Vector3 a, Vector3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::cross(Vector3& a, Vector3& b)
{
    return Vector3(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}

Vector3 Vector3::normalize(Vector3& a)
{
    return a / std::sqrt(dot(a, a));
}

std::tuple<Vector3, Vector3> Vector3::tangentSpace(const Vector3& n)
{
    const double s = std::copysign(1, n.z);
    const double a = -1 / (s + n.z);
    const double b = n.x*n.y*a;
    return
    {
        Vector3(1 + s * n.x*n.x*a,s*b,-s * n.x),
        Vector3(b,s + n.y*n.y*a,-n.y)
    };
}
