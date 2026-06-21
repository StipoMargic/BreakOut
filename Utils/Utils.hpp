//
// Created by stipo on 09. 04. 2020..
//


#ifndef UTILS_UTILS_HPP
#define UTILS_UTILS_HPP

inline constexpr float EPSILON = 0.0001f;
inline constexpr float PI = 3.14159f;
inline constexpr float TWO_PI = 2.0f * PI;
[[nodiscard]] bool IsEqual(float x, float y);
[[nodiscard]] bool IsGreaterThanOrEqual(float x, float y);
[[nodiscard]] bool IsLessThanOrEqual(float x, float y);
[[nodiscard]] float MillisecondsToSeconds(unsigned int milliseconds);
#endif