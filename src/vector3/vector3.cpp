#include "vector3.h"

constexpr Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

void Vector3::normalize()
{
    const auto n = norm();
    if (n != 0)
    {
        x /= n;
        y /= n;
        z /= n;
    }
}

Vector3 Vector3::operator*(float scalar) const
{
    return {x * scalar, y * scalar, z * scalar};
}

Vector3 Vector3::operator/(float scalar) const
{
    return {x / scalar, y / scalar, z / scalar};
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
    const float epsilon = 1e-6f;
    return std::fabs(x - other.x) < epsilon &&
           std::fabs(y - other.y) < epsilon &&
           std::fabs(z - other.z) < epsilon;
}

std::string Vector3::to_string() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}