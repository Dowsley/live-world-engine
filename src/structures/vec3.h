#pragma once

#include <fstream>

#include "vec2.h"

class Vec3 final
{
    public:
        Vec3();
        Vec3(const Vec2& v, int z);
        Vec3(int x, int y, int z);

        // No, I'm not gonna respect standard names here. I want it to be short.
        [[nodiscard]] int x() const;
        [[nodiscard]] int y() const;
        [[nodiscard]] int z() const;
        [[nodiscard]] int width() const;
        [[nodiscard]] int height() const;
        [[nodiscard]] int depth() const;


        // here I will
        [[nodiscard]] int GetFlattenedSize() const;
        void SetX(int x);
        void SetY(int y);
        void SetZ(int z);

        [[nodiscard]] std::string ToString() const;

        Vec3 operator-() const;
        int operator[](int i) const;
        int& operator[](int i);
        bool operator==(const Vec3 &v) const;

        Vec3& operator+=(const Vec3 &v);
        Vec3& operator+=(int t);
        Vec3& operator*=(int t);
        Vec3& operator/=(int t);

        friend Vec3 operator+(const Vec3 &u, const Vec3 &v);
        friend Vec3 operator+(const Vec3 &u, int val);
        friend Vec3 operator+(int val, const Vec3 &u);
        friend Vec3 operator-(const Vec3 &u, const Vec3 &v);
        friend Vec3 operator*(const Vec3 &u, const Vec3 &v);
        friend Vec3 operator*(int t, const Vec3 &v);
        friend Vec3 operator*(const Vec3 &v, int t);
        friend Vec3 operator/(Vec3 v, int t);
        friend std::ostream& operator<<(std::ostream &out, const Vec3 &v);

    protected:
        int e[3]{};
};
