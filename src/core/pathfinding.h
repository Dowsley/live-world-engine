#pragma once

#include <set>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

#include "../structures/vec3.h"
#include "world.h"

class World;
class CreatureManager;

class PFNode {
public:
    PFNode *parent{};
    Vec3 position;
    float gCost{}; // Cost from start node to this node
    float hCost{}; // Heuristic estimate from this node to goal

    PFNode() = default;
    PFNode(PFNode *parent, Vec3 position, float gCost, float hCost);
    [[nodiscard]] float fCost() const;
};

class Pathfinding {
public:
    Pathfinding() = default;
    static std::list<Vec3> FindPath(const World *world, const Vec3 &start, const Vec3 &end, bool debug=false);
    static bool _isValid(const World *world, const Vec3 &pos);
    static float _heuristic(const World *world, const Vec3 &a, const Vec3 &b);
};
