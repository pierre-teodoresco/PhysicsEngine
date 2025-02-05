#pragma once

#include <cmath>
#include <string>

/**
 * @brief A 3D vector
 */
class Vector3
{
public:
    constexpr Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {};

    /**
     * @brief Get the zero vector
     * @return The zero vector
     */
    static const Vector3 zero() { return {0.0f, 0.0f, 0.0f}; }

    /**
     * @brief Get the x component
     * @return The x component
     */
    float getX() const { return x; }

    /**
     * @brief Get the y component
     * @return The y component
     */
    float getY() const { return y; }

    /**
     * @brief Get the z component
     * @return The z component
     */
    float getZ() const { return z; }

    /**
     * @brief Norm of the vector
     * @return The norm
     */
    float norm() const { return std::hypot(x, y, z); }

    /**
     * @brief Squared norm of the vector
     * @return The squared norm
     */
    float squaredNorm() const { return x * x + y * y + z * z; }

    /**
     * @brief Normalize the vector in place
     */
    void normalize();

    /**
     * @brief Multiply the vector by a scalar
     * @param scalar The scalar
     * @return The result
     */
    Vector3 operator*(float scalar) const;

    /**
     * @brief Divide the vector by a scalar
     * @param scalar The scalar
     * @return The result
     */
    Vector3 operator/(float scalar) const;

    /**
     * @brief Add two vectors
     * @param other The other vector
     * @return The result
     */
    Vector3 operator+(const Vector3 &other) const;

    /**
     * @brief Add a vector to this vector
     * @param other The other vector
     */
    void operator+=(const Vector3 &other);

    /**
     * @brief Subtract two vectors
     * @param other The other vector
     * @return The result
     */
    Vector3 operator-(const Vector3 &other) const;

    /**
     * @brief Subtract a vector from this vector
     * @param other The other vector
     */
    void operator-=(const Vector3 &other);

    /**
     * @brief Negate the vector
     * @return The result
     */
    Vector3 operator-() const;

    /**
     * @brief Cross product of two vectors
     * @param other The other vector
     * @return The result
     */
    Vector3 operator*(const Vector3 &other) const;

    /**
     * @brief Dot (scalar) product of two vectors
     * @param other The other vector
     * @return The result
     */
    float dot(const Vector3 &other) const;

    /**
     * @brief Component product of two vectors
     * @param other The other vector
     * @return The result
     */
    Vector3 componentProduct(const Vector3 &other) const;

    /**
     * @brief == operator
     * @return True if the vectors are equal (within 1e-6f epsilon), false otherwise
     */
    bool operator==(const Vector3 &other) const;

    /**
     * @brief Convert the vector to a string for debugging
     * @return The string
     */
    std::string to_string() const;

private:
    float x, y, z;
};