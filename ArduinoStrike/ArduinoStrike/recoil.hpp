#pragma once
#include <iostream>
#include <basetsd.h>

struct C_UTL_VECTOR
{
    DWORD64 count = 0;
    DWORD64 data = 0;
};

struct Vec3 {
    float x, y, z;
    Vec3() : x(0.f), y(0.f), z(0.f) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3& d) const {
        return { x + d.x, y + d.y, z + d.z };
    }
    Vec3 operator-(const Vec3& d) const {
        return { x - d.x, y - d.y, z - d.z };
    }
    Vec3 operator*(const Vec3& d) const {
        return { x * d.x, y * d.y, z * d.z };
    }
    Vec3 operator*(float scalar) const {
        return { x * scalar, y * scalar, z * scalar };
    }
    friend Vec3 operator*(float scalar, const Vec3& v) {
        return { v.x * scalar, v.y * scalar, v.z * scalar };
    }
    void Normalize() {
        while (y < -180) y += 360;
        while (y > 180) y -= 360;
        if (x > 89) x = 89;
        if (x < -89) x = -89;
    }
};

struct Vec2 {
    float x, y;
    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2 operator+(const Vec2& d) const {
        return { x + d.x, y + d.y };
    }
    Vec2 operator-(const Vec2& d) const {
        return { x - d.x, y - d.y };
    }
    Vec2 operator*(const Vec2& d) const {
        return { x * d.x, y * d.y };
    }
    Vec2 operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }
    void Normalize() {
        while (y < -180) y += 360;
        while (y > 180) y -= 360;
        if (x > 89) x = 89;
        if (x < -89) x = -89;
    }
};