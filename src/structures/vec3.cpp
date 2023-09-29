#include "vec3.h"

#include <cmath>
#include <string>

Vec3::Vec3()
{
   e[0] = 0;
   e[1] = 0;
   e[2] = 0;
}


Vec3::Vec3(Vec2 v, int z)
{
    e[0] = v.x;
    e[1] = v.y;
    e[2] = z;
}

Vec3::Vec3(int x, int y, int z)
{
    e[0] = x;
    e[1] = y;
    e[2] = z;
}

int Vec3::x() const { return e[0]; }
int Vec3::y() const { return e[1]; }
int Vec3::z() const { return e[2]; }
int Vec3::width() const { return x(); }
int Vec3::height() const { return y(); }
int Vec3::depth() const { return z(); }

int Vec3::GetFlattenedSize() const { return e[0] * e[1] * e[2]; }

void Vec3::SetX(int x) { e[0] = x; }
void Vec3::SetY(int y) { e[1] = y; }
void Vec3::SetZ(int z) { e[2] = z; }

std::string Vec3::ToString() const
{
    return std::to_string(e[0]) + " " + std::to_string(e[1]) + " " + std::to_string(e[2]);
}

Vec3 Vec3::operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
int Vec3::operator[](int i) const { return e[i]; }
int& Vec3::operator[](int i) { return e[i]; }

bool Vec3::operator==(const Vec3 &v) const
{
    return e[0] == v[0]
        && e[1] == v[1]
        && e[2] == v[2];
}

Vec3& Vec3::operator+=(const Vec3 &v)
{
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];
    return *this;
}

Vec3& Vec3::operator+=(const int t)
{
    e[0] += t;
    e[1] += t;
    e[2] += t;
    return *this;
}

Vec3& Vec3::operator*=(const int t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

Vec3& Vec3::operator/=(const int t)
{
    return *this *= 1/t;
}

Vec3 operator+(const Vec3 &u, const Vec3 &v) { return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]); }
Vec3 operator+(const Vec3 &u, int val) { return Vec3(u[0] + val, u[1] + val, u[2] + val); } 
Vec3 operator+(int val, const Vec3 &u) { return u + val; } 
Vec3 operator-(const Vec3 &u, const Vec3 &v) { return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]); }
Vec3 operator*(const Vec3 &u, const Vec3 &v) { return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]); }
Vec3 operator*(int t, const Vec3 &v) { return Vec3(t*v[0], t*v[1], t*v[2]); }
Vec3 operator*(const Vec3 &v, int t) { return t * v; }
Vec3 operator/(Vec3 v, int t) { return (1/t) * v; }
std::ostream& operator<<(std::ostream &out, const Vec3 &v) { return out << "Vec3(" << v[0] << ' ' << v[1] << ' ' << v[2] << ")"; }
