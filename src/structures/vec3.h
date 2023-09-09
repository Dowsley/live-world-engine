#pragma once

#include <fstream>

class Vec3 final
{
    public:
        Vec3();
        Vec3(int x, int y, int z);

        // No, I'm not gonna respect standard names here. I want it to be short.
        int x() const;
        int y() const;
        int z() const;
        int width() const;
        int height() const;
        int depth() const;


        // here I will
        int GetFlattenedSize() const;
        void SetX(int x);
        void SetY(int y);
        void SetZ(int z);

        Vec3 operator-() const;
        int operator[](int i) const;
        int& operator[](int i);

        Vec3& operator+=(const Vec3 &v);
        Vec3& operator+=(const int t);
        Vec3& operator*=(const int t);
        Vec3& operator/=(const int t);

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
        int e[3];
};
