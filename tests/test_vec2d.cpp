#include "doctest.h"

#include "Vec2D.hpp"
#include "Utils.hpp"

#include <cmath>

namespace
{
bool Approx(const Vec2D& a, const Vec2D& b)
{
    return a.GetX() == doctest::Approx(b.GetX()) && a.GetY() == doctest::Approx(b.GetY());
}
}  // namespace

TEST_CASE("Construction and accessors")
{
    Vec2D v(3.0f, -4.0f);
    CHECK(v.GetX() == doctest::Approx(3.0f));
    CHECK(v.GetY() == doctest::Approx(-4.0f));
    CHECK(Vec2D::Zero.GetX() == doctest::Approx(0.0f));
    CHECK(Vec2D::Zero.GetY() == doctest::Approx(0.0f));
}

TEST_CASE("Equality uses epsilon tolerance")
{
    CHECK(Vec2D(1.0f, 2.0f) == Vec2D(1.0f, 2.0f));
    CHECK(Vec2D(1.0f, 2.0f) != Vec2D(1.0f, 2.5f));
}

TEST_CASE("Arithmetic operators")
{
    Vec2D a(1.0f, 2.0f);
    Vec2D b(3.0f, 4.0f);

    CHECK(Approx(a + b, Vec2D(4.0f, 6.0f)));
    CHECK(Approx(b - a, Vec2D(2.0f, 2.0f)));
    CHECK(Approx(a * 2.0f, Vec2D(2.0f, 4.0f)));
    CHECK(Approx(2.0f * a, Vec2D(2.0f, 4.0f)));     // scalar-on-left friend
    CHECK(Approx(b / 2.0f, Vec2D(1.5f, 2.0f)));
    CHECK(Approx(-a, Vec2D(-1.0f, -2.0f)));

    SUBCASE("compound assignment")
    {
        Vec2D c = a;
        c += b;
        CHECK(Approx(c, Vec2D(4.0f, 6.0f)));
        c -= b;
        CHECK(Approx(c, a));
        c *= 3.0f;
        CHECK(Approx(c, Vec2D(3.0f, 6.0f)));
        c /= 3.0f;
        CHECK(Approx(c, a));
    }
}

TEST_CASE("Magnitude and distance")
{
    Vec2D v(3.0f, 4.0f);
    CHECK(v.Mag2() == doctest::Approx(25.0f));
    CHECK(v.Mag() == doctest::Approx(5.0f));
    CHECK(Vec2D::Zero.Distance(v) == doctest::Approx(5.0f));
}

TEST_CASE("Dot and Cross")
{
    CHECK(Vec2D(1.0f, 0.0f).Dot(Vec2D(0.0f, 1.0f)) == doctest::Approx(0.0f));  // orthogonal
    CHECK(Vec2D(1.0f, 2.0f).Dot(Vec2D(3.0f, 4.0f)) == doctest::Approx(11.0f));

    CHECK(Vec2D(1.0f, 0.0f).Cross(Vec2D(0.0f, 1.0f)) == doctest::Approx(1.0f));
    CHECK(Vec2D(2.0f, 3.0f).Cross(Vec2D(4.0f, 5.0f)) == doctest::Approx(2.0f * 5.0f - 3.0f * 4.0f));
}

TEST_CASE("Normalize and unit vector")
{
    Vec2D v(0.0f, 5.0f);
    CHECK(v.GetUnitVec().Mag() == doctest::Approx(1.0f));
    CHECK(Approx(v.GetUnitVec(), Vec2D(0.0f, 1.0f)));

    Vec2D n(3.0f, 4.0f);
    n.Normalize();
    CHECK(n.Mag() == doctest::Approx(1.0f));

    // Zero vector cannot be normalized -> stays Zero (epsilon guard).
    CHECK(Approx(Vec2D::Zero.GetUnitVec(), Vec2D::Zero));
}

TEST_CASE("ProjectOnto and AngleBetween")
{
    CHECK(Approx(Vec2D(2.0f, 2.0f).ProjectOnto(Vec2D(1.0f, 0.0f)), Vec2D(2.0f, 0.0f)));
    CHECK(Vec2D(1.0f, 0.0f).AngleBetween(Vec2D(0.0f, 1.0f)) == doctest::Approx(PI / 2.0f));
}

TEST_CASE("Reflect about a surface normal")
{
    // Ball travelling down-right bounces off a horizontal floor (normal (0,1)).
    CHECK(Approx(Vec2D(1.0f, -1.0f).Reflect(Vec2D(0.0f, 1.0f)), Vec2D(1.0f, 1.0f)));
    // Bounce off a vertical wall (normal (1,0)).
    CHECK(Approx(Vec2D(-1.0f, 1.0f).Reflect(Vec2D(1.0f, 0.0f)), Vec2D(1.0f, 1.0f)));
}

TEST_CASE("Rotate mutates, RotationResult does not")
{
    SUBCASE("RotationResult around origin")
    {
        Vec2D v(1.0f, 0.0f);
        Vec2D r = v.RotationResult(PI / 2.0f, Vec2D::Zero);
        CHECK(Approx(r, Vec2D(0.0f, 1.0f)));
        CHECK(Approx(v, Vec2D(1.0f, 0.0f)));        // original untouched
    }

    SUBCASE("Rotate around a pivot mutates in place")
    {
        Vec2D v(2.0f, 1.0f);
        v.Rotate(PI / 2.0f, Vec2D(1.0f, 1.0f));     // rotate about (1,1)
        CHECK(Approx(v, Vec2D(1.0f, 2.0f)));
    }
}
