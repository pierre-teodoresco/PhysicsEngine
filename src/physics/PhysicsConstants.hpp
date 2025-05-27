#pragma once

namespace pe
{
    // FORCES
    constexpr float GRAVITY = 9.81f;         // Standard gravity in m/s^2
    constexpr float PIXELS_PER_METER = 55.f; // Conversion factor for pixels to meters in the physics engine

    // FLOAT PRECISION
    constexpr float EPSILON = 1e-6f; // Small value to compare floating-point numbers
}