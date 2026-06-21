#include "doctest.h"

#include "AaRectangle.hpp"
#include "Vec2D.hpp"

TEST_CASE("Both constructors describe the same rectangle")
{
    // width/height ctor uses an inclusive span: bottomRight = topLeft + (w-1, h-1).
    AARectangle a(Vec2D(0.0f, 0.0f), 10u, 6u);
    AARectangle b(Vec2D(0.0f, 0.0f), Vec2D(9.0f, 5.0f));

    CHECK(a.GetTopLeft() == b.GetTopLeft());
    CHECK(a.GetBottomRight() == b.GetBottomRight());
    CHECK(a.GetWidth() == doctest::Approx(10.0f));
    CHECK(a.GetHeight() == doctest::Approx(6.0f));
}

TEST_CASE("GetCenter")
{
    AARectangle r(Vec2D(0.0f, 0.0f), Vec2D(10.0f, 10.0f));
    // width/height are 11 (inclusive), so center = topLeft + 11/2.
    CHECK(r.GetCenter().GetX() == doctest::Approx(5.5f));
    CHECK(r.GetCenter().GetY() == doctest::Approx(5.5f));
}

TEST_CASE("ContainsPoint is inclusive of the edges")
{
    AARectangle r(Vec2D(0.0f, 0.0f), Vec2D(10.0f, 10.0f));

    CHECK(r.ContainsPoint(Vec2D(5.0f, 5.0f)));      // inside
    CHECK(r.ContainsPoint(Vec2D(0.0f, 0.0f)));      // on the top-left corner
    CHECK(r.ContainsPoint(Vec2D(10.0f, 10.0f)));    // on the bottom-right corner
    CHECK_FALSE(r.ContainsPoint(Vec2D(-1.0f, 5.0f)));
    CHECK_FALSE(r.ContainsPoint(Vec2D(5.0f, 11.0f)));
}

TEST_CASE("Intersects covers every separating-axis branch")
{
    AARectangle base(Vec2D(0.0f, 0.0f), Vec2D(10.0f, 10.0f));

    CHECK(base.Intersects(AARectangle(Vec2D(5.0f, 5.0f), Vec2D(15.0f, 15.0f))));   // overlap
    CHECK(base.Intersects(AARectangle(Vec2D(2.0f, 2.0f), Vec2D(4.0f, 4.0f))));     // contained

    CHECK_FALSE(base.Intersects(AARectangle(Vec2D(20.0f, 0.0f), Vec2D(30.0f, 10.0f))));  // to the right
    CHECK_FALSE(base.Intersects(AARectangle(Vec2D(-30.0f, 0.0f), Vec2D(-20.0f, 10.0f)))); // to the left
    CHECK_FALSE(base.Intersects(AARectangle(Vec2D(0.0f, 20.0f), Vec2D(10.0f, 30.0f))));  // below
    CHECK_FALSE(base.Intersects(AARectangle(Vec2D(0.0f, -30.0f), Vec2D(10.0f, -20.0f)))); // above
}

TEST_CASE("MoveTo preserves dimensions")
{
    AARectangle r(Vec2D(0.0f, 0.0f), 10u, 6u);
    r.MoveTo(Vec2D(100.0f, 50.0f));

    CHECK(r.GetTopLeft() == Vec2D(100.0f, 50.0f));
    CHECK(r.GetWidth() == doctest::Approx(10.0f));
    CHECK(r.GetHeight() == doctest::Approx(6.0f));
}

TEST_CASE("Inset shrinks by twice the insets")
{
    AARectangle r(Vec2D(0.0f, 0.0f), 20u, 20u);
    Vec2D insets(2.0f, 3.0f);
    AARectangle inner = AARectangle::Inset(r, insets);

    CHECK(inner.GetTopLeft() == Vec2D(2.0f, 3.0f));
    CHECK(inner.GetWidth() == doctest::Approx(20.0f - 2.0f * 2.0f));
    CHECK(inner.GetHeight() == doctest::Approx(20.0f - 2.0f * 3.0f));
}

TEST_CASE("GetPoints returns the four corners")
{
    AARectangle r(Vec2D(0.0f, 0.0f), Vec2D(10.0f, 5.0f));
    auto pts = r.GetPoints();

    REQUIRE(pts.size() == 4);
    CHECK(pts[0] == Vec2D(0.0f, 0.0f));     // top-left
    CHECK(pts[1] == Vec2D(10.0f, 0.0f));    // top-right
    CHECK(pts[2] == Vec2D(10.0f, 5.0f));    // bottom-right
    CHECK(pts[3] == Vec2D(0.0f, 5.0f));     // bottom-left
}
