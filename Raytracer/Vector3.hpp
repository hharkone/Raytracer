#pragma once
#include <algorithm>
#include <tuple>

class Vector3
{
public:

    double x, y, z;

    ~Vector3();

    Vector3(double v = 0) : Vector3(v, v, v) {}
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    double operator[](int i)
    {
        return (&x)[i];
    }
    const double &operator[](int i) const
    {
        return (&x)[i];
    }

    Vector3 operator+(Vector3& a);
    Vector3 operator-(Vector3& a);
    Vector3 operator*(Vector3& a);
    Vector3 operator/(Vector3& a);
    Vector3 operator-(double scalar);
    Vector3 operator*(double scalar);
    Vector3 operator/(double scalar);

    const Vector3 operator+(const Vector3& a) const;
    const Vector3 operator-(const Vector3& a) const;
    const Vector3 operator*(const double scalar) const;
    const Vector3 operator/(const double scalar) const;

    static double dot(Vector3 a, Vector3 b);
    static Vector3 cross(Vector3 a, Vector3 b);
    static Vector3 normalize(Vector3 a);
    std::tuple<Vector3, Vector3> tangentSpace(const Vector3& n);
};
