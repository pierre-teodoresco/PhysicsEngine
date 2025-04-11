#pragma once

#include "vector3/vector3.h"

namespace pe
{
    /**
     * @brief The integrator class
     */
    class Integrator
    {
    public:
        Integrator() = default;
        virtual ~Integrator() = default;

        virtual void integrate(float dt, Vector3 &position, Vector3 &velocity, Vector3 &acceleration) = 0;
    };

    /**
     * @brief The Euler integrator class
     */
    class Euler : public Integrator
    {
    public:
        Euler() = default;
        ~Euler() = default;

        void integrate(float dt, Vector3 &position, Vector3 &velocity, Vector3 &acceleration) override;
    };

    /**
     * @brief The Verlet integrator class
     */
    class Verlet : public Integrator
    {
    public:
        Verlet() = default;
        ~Verlet() = default;

        void integrate(float dt, Vector3 &position, Vector3 &velocity, Vector3 &acceleration) override;

    private:
        Vector3 oldPosition;
        bool firstFrame = true;
    };
}