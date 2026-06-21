//
// Created by stipo on 09. 04. 2020..
//

#ifndef UTILS_VEC2D_HPP
#define UTILS_VEC2D_HPP

#include <iostream>

class Vec2D
{
  public:
    static const Vec2D Zero;

    Vec2D() : Vec2D(0, 0) {}

    Vec2D(float x, float y) : mX(x), mY(y) {}

    inline void SetX(float x) { mX = x; }

    inline void SetY(float y) { mY = y; }

    [[nodiscard]] inline float GetX() const { return mX; }

    [[nodiscard]] inline float GetY() const { return mY; }

    friend std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec);
    bool operator==(const Vec2D& vec2) const;
    bool operator!=(const Vec2D& vec2) const;
    Vec2D operator-() const;
    Vec2D operator*(float scale) const;
    Vec2D operator/(float scale) const;
    Vec2D& operator*=(float scale);
    Vec2D& operator/=(float scale);
    Vec2D operator+(const Vec2D& vec) const;
    Vec2D operator-(const Vec2D& vec) const;
    Vec2D& operator+=(const Vec2D& vec);
    Vec2D& operator-=(const Vec2D& vec);
    [[nodiscard]] float Mag2() const;
    [[nodiscard]] float Mag() const;
    [[nodiscard]] Vec2D GetUnitVec() const;
    Vec2D& Normalize();
    [[nodiscard]] float Distance(const Vec2D& vec) const;
    [[nodiscard]] float Dot(const Vec2D& vec) const;
    [[nodiscard]] float Cross(const Vec2D& vec) const;
    [[nodiscard]] Vec2D ProjectOnto(const Vec2D& vec2) const;
    [[nodiscard]] float AngleBetween(const Vec2D& vec2) const;
    [[nodiscard]] Vec2D Reflect(const Vec2D& normal) const;
    void Rotate(float angle, const Vec2D& aroundPoint);
    [[nodiscard]] Vec2D RotationResult(float angle, const Vec2D& aroundPoint) const;
    friend Vec2D operator*(float scalar, const Vec2D& vec);

  private:
    float mX, mY;
};

#endif
