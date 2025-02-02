#pragma once

/**
 * @brief A 3D vector
 */
class Vector3
{
public:
    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    float x;
    float y;
    float z;

    /**
     * @brief Norm of the vector
     * @return The norm
     */
    float norm() const;

    /**
     * @brief Squared norm of the vector
     * @return The squared norm
     */
    float squaredNorm() const;

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
     * @return True if the vectors are equal
     */
    bool operator==(const Vector3 &other) const;
};