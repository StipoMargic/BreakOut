#include "doctest.h"

#include "Utils.hpp"

TEST_CASE("IsEqual respects EPSILON tolerance")
{
    CHECK(IsEqual(1.0f, 1.0f));
    CHECK(IsEqual(1.0f, 1.0f + EPSILON / 2.0f));
    CHECK_FALSE(IsEqual(1.0f, 1.0f + EPSILON * 2.0f));
}

TEST_CASE("IsGreaterThanOrEqual / IsLessThanOrEqual at the boundary")
{
    CHECK(IsGreaterThanOrEqual(2.0f, 1.0f));
    CHECK(IsGreaterThanOrEqual(1.0f, 1.0f)); // equal within epsilon
    CHECK_FALSE(IsGreaterThanOrEqual(1.0f, 2.0f));

    CHECK(IsLessThanOrEqual(1.0f, 2.0f));
    CHECK(IsLessThanOrEqual(1.0f, 1.0f)); // equal within epsilon
    CHECK_FALSE(IsLessThanOrEqual(2.0f, 1.0f));
}

TEST_CASE("MillisecondsToSeconds converts correctly")
{
    CHECK(MillisecondsToSeconds(1500) == doctest::Approx(1.5f));
    CHECK(MillisecondsToSeconds(0) == doctest::Approx(0.0f));
    CHECK(MillisecondsToSeconds(1000) == doctest::Approx(1.0f));
}
