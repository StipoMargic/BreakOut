#include "doctest.h"

#include "Circle.hpp"
#include "Vec2D.hpp"

TEST_CASE("Accessors and SetRadius")
{
    Circle c(Vec2D(1.0f, 2.0f), 5.0f);
    CHECK(c.GetCenter() == Vec2D(1.0f, 2.0f));
    CHECK(c.GetRadius() == doctest::Approx(5.0f));

    c.SetRadius(10.0f);
    CHECK(c.GetRadius() == doctest::Approx(10.0f));
}

TEST_CASE("Contains is inclusive of the boundary")
{
    Circle c(Vec2D(0.0f, 0.0f), 5.0f);

    CHECK(c.Contains(Vec2D(0.0f, 0.0f)));       // center
    CHECK(c.Contains(Vec2D(3.0f, 4.0f)));       // exactly on the boundary (dist == 5)
    CHECK_FALSE(c.Contains(Vec2D(5.0f, 5.0f))); // outside
}

TEST_CASE("Intersects uses a strict less-than (tangent circles do NOT intersect)")
{
    Circle c(Vec2D(0.0f, 0.0f), 5.0f);

    CHECK(c.Intersects(Circle(Vec2D(4.0f, 0.0f), 5.0f)));        // clear overlap
    CHECK_FALSE(c.Intersects(Circle(Vec2D(20.0f, 0.0f), 5.0f))); // far apart

    // Tangent: distance (10) == r1 + r2 (10). Current semantics: strict '<' => false.
    CHECK_FALSE(c.Intersects(Circle(Vec2D(10.0f, 0.0f), 5.0f)));
}
