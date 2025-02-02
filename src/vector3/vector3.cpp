#include "vector3.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

float Vector3::norm() const
{
    return std::sqrt(squaredNorm());
}

float Vector3::squaredNorm() const
{
    return x * x + y * y + z * z;
}

void Vector3::normalize()
{
    const auto n = norm();
    x /= n;
    y /= n;
    z /= n;
}

Vector3 Vector3::operator*(float scalar) const
{
    return {x * scalar, y * scalar, z * scalar};
}

Vector3 Vector3::operator+(const Vector3 &other) const
{
    return {x + other.x, y + other.y, z + other.z};
}

void Vector3::operator+=(const Vector3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}

Vector3 Vector3::operator-(const Vector3 &other) const
{
    return {x - other.x, y - other.y, z - other.z};
}

void Vector3::operator-=(const Vector3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

Vector3 Vector3::operator-() const
{
    return {-x, -y, -z};
}

Vector3 Vector3::operator*(const Vector3 &other) const
{
    return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
}

float Vector3::dot(const Vector3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::componentProduct(const Vector3 &other) const
{
    return {x * other.x, y * other.y, z * other.z};
}

bool Vector3::operator==(const Vector3 &other) const
{
    return x == other.x && y == other.y && z == other.z;
}