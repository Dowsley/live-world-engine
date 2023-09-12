#pragma once

#include "../structures/vec2.h"
#include "../structures/vec3.h"

namespace GeometryUtils
{
    int Flatten3DCoords(const Vec3 &pos, const Vec3 &dimensions);
    int Flatten2DCoords(const Vec2 &pos, const Vec3 &dimensions);
};
