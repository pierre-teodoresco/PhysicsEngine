# PhysicsEngine

## Author
- Pierre Teodoresco - 3A SN

## Description
Currently the demo is a simple balistic simulation in 2D. The user can shoot a particle with a given angle and speed by clicking on the screen. The particle will then follow a parabolic trajectory.

## Run
To run the project, you can use the following command:
```bash
cmake -S . -B build
cmake --build build --target physics_engine
./build/bin/physics_engine
```

## Unit tests
To run the Vector3 unit tests, you can use the following command:
```bash
cmake -S . -B build
cmake --build build --target test_vector3
./build/bin/test_vector3
```