#include "geometry.h"

int GeometryUtils::Flatten3DCoords(const Vec3 &pos, const Vec3 &dimensions)
{
    return pos.y() + dimensions.height() * (pos.x() + dimensions.width() * pos.z());
}

int GeometryUtils::Flatten2DCoords(const Vec2 &pos, const Vec3 &dimensions)
{
    return pos.y * dimensions.width() + pos.x;
}

