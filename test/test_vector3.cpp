#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "vector3/vector3.h"
#include <cmath>

TEST_CASE("a Vector3 can be declared", "[vector3]")
{
    Vector3 v;
    REQUIRE(v.getX() == 0);
    REQUIRE(v.getY() == 0);
    REQUIRE(v.getZ() == 0);

    Vector3 v2(1, 2, 3);
    REQUIRE(v2.getX() == 1);
    REQUIRE(v2.getY() == 2);
    REQUIRE(v2.getZ() == 3);
}

TEST_CASE("a null Vector3 can be declared", "[vector3]")
{
    Vector3 v = Vector3::zero();
    REQUIRE(v.getX() == 0);
    REQUIRE(v.getY() == 0);
    REQUIRE(v.getZ() == 0);
}

TEST_CASE("norm of a Vector3 can be computed", "[vector3]")
{
    Vector3 v(1, 2, 3);
    REQUIRE(v.norm() == Catch::Approx(std::sqrt(14)));
}

TEST_CASE("squared norm of a Vector3 can be computed", "[vector3]")
{
    Vector3 v(1, 2, 3);
    REQUIRE(v.squaredNorm() == 14);
}

TEST_CASE("a Vector3 can be normalize", "[vector3]")
{
    Vector3 v(1, 2, 3);
    v.normalize();
    REQUIRE(v.getX() == Catch::Approx(0.2672612419124244));
    REQUIRE(v.getY() == Catch::Approx(0.5345224838248488));
    REQUIRE(v.getZ() == Catch::Approx(0.8017837257372732));
}

TEST_CASE("a Vector3 can be multiply by a scalar", "[vector3]")
{
    Vector3 v(1, 2, 3);
    auto result = v * 2;
    REQUIRE(result.getX() == 2);
    REQUIRE(result.getY() == 4);
    REQUIRE(result.getZ() == 6);
}

TEST_CASE("two Vector3 can be added", "[vector3]")
{
    Vector3 v(1, 2, 3);
    Vector3 v2(4, 5, 6);
    auto result = v + v2;
    REQUIRE(result.getX() == 5);
    REQUIRE(result.getY() == 7);
    REQUIRE(result.getZ() == 9);
}

TEST_CASE("a Vector3 can be added to another", "[vector3]")
{
    Vector3 v(1, 2, 3);
    Vector3 v2(4, 5, 6);
    v += v2;
    REQUIRE(v.getX() == 5);
    REQUIRE(v.getY() == 7);
    REQUIRE(v.getZ() == 9);
}

TEST_CASE("two Vector3 can be subtracted", "[vector3]")
{
    Vector3 v(1, 2, 3);
    Vector3 v2(4, 5, 6);
    auto result = v - v2;
    REQUIRE(result.getX() == -3);
    REQUIRE(result.getY() == -3);
    REQUIRE(result.getZ() == -3);
}

TEST_CASE("a Vector3 can be subtracted to another", "[vector3]")
{
    Vector3 v(1, 2, 3);
    Vector3 v2(4, 5, 6);
    v -= v2;
    REQUIRE(v.getX() == -3);
    REQUIRE(v.getY() == -3);
    REQUIRE(v.getZ() == -3);
}

TEST_CASE("a Vector3 can be negated", "[vector3]")
{
    Vector3 v(1, 2, 3);
    auto result = -v;
    REQUIRE(result.getX() == -1);
    REQUIRE(result.getY() == -2);
    REQUIRE(result.getZ() == -3);
}

TEST_CASE("the cross product between two Vector3 can be computed", "[vector3]")
{
    Vector3 v(1, 2, 3);
    Vector3 v2(4, 5, 6);
    auto result = v * v2;
    REQUIRE(result.getX() == -3);
    REQUIRE(result.getY() == 6);
    REQUIRE(result.getZ() == -3);
}

TEST_CASE("the dot product between two Vector3 can be computed", "[vector3]")
{
    Vector3 v(1, 2, 3);
    Vector3 v2(4, 5, 6);
    REQUIRE(v.dot(v2) == 32);
}

TEST_CASE("the components product between two Vector3 can be computed", "[vector3]")
{
    Vector3 v(1, 2, 3);
    Vector3 v2(4, 5, 6);
    auto result = v.componentProduct(v2);
    REQUIRE(result.getX() == 4);
    REQUIRE(result.getY() == 10);
    REQUIRE(result.getZ() == 18);
}

TEST_CASE("the equality operator can be applied between two Vector3", "[vector3]")
{
    Vector3 v(1, 2, 3);
    Vector3 v2(1, 2, 3);
    REQUIRE(v == v2);
}