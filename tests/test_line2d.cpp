#include "doctest.h"

#include "Line2D.hpp"
#include "Vec2D.hpp"

TEST_CASE("Length and Midpoint")
{
    Line2D line(Vec2D(0.0f, 0.0f), Vec2D(3.0f, 4.0f));
    CHECK(line.Length() == doctest::Approx(5.0f));

    Line2D seg(Vec2D(0.0f, 0.0f), Vec2D(4.0f, 4.0f));
    CHECK(seg.Midpoint() == Vec2D(2.0f, 2.0f));
}

TEST_CASE("ClosestPoint on an infinite line vs a clamped segment")
{
    Line2D line(Vec2D(0.0f, 0.0f), Vec2D(10.0f, 0.0f));

    SUBCASE("foot of perpendicular lies on the segment")
    {
        CHECK(line.ClosestPoint(Vec2D(5.0f, 5.0f)) == Vec2D(5.0f, 0.0f));
    }

    SUBCASE("infinite line projects past the endpoints (t < 0 and t > 1)")
    {
        CHECK(line.ClosestPoint(Vec2D(-5.0f, 3.0f)) == Vec2D(-5.0f, 0.0f));
        CHECK(line.ClosestPoint(Vec2D(15.0f, 3.0f)) == Vec2D(15.0f, 0.0f));
    }

    SUBCASE("segment clamps to the endpoints")
    {
        CHECK(line.ClosestPoint(Vec2D(-5.0f, 3.0f), true) == Vec2D(0.0f, 0.0f));
        CHECK(line.ClosestPoint(Vec2D(15.0f, 3.0f), true) == Vec2D(10.0f, 0.0f));
    }
}

TEST_CASE("DistanceFromPoint measures from the query point, not the endpoint")
{
    Line2D line(Vec2D(0.0f, 0.0f), Vec2D(10.0f, 0.0f));

    // Closest point to (5,5) on the line is (5,0); distance is 5.
    CHECK(line.DistanceFromPoint(Vec2D(5.0f, 5.0f)) == doctest::Approx(5.0f));
    // Clamped to the segment, closest point to (15,0) is (10,0); distance is 5.
    CHECK(line.DistanceFromPoint(Vec2D(15.0f, 0.0f), true) == doctest::Approx(5.0f));

    // MinDistanceFrom is the known-correct reference; the two must agree.
    CHECK(line.DistanceFromPoint(Vec2D(5.0f, 5.0f))
          == doctest::Approx(line.MinDistanceFrom(Vec2D(5.0f, 5.0f))));
}

TEST_CASE("operator==")
{
    CHECK(Line2D(Vec2D(0.0f, 0.0f), Vec2D(1.0f, 1.0f))
          == Line2D(Vec2D(0.0f, 0.0f), Vec2D(1.0f, 1.0f)));
    CHECK_FALSE(Line2D(Vec2D(0.0f, 0.0f), Vec2D(1.0f, 1.0f))
                == Line2D(Vec2D(0.0f, 0.0f), Vec2D(2.0f, 2.0f)));
}
