#include <iostream>
#include <unordered_set>

#include "pathfinding.h"

struct Vec3Hasher {
    std::size_t operator()(const Vec3 &v) const {
        return ((std::hash<int>()(v.x()) ^ (std::hash<int>()(v.y()) << 1)) >> 1) ^ (std::hash<int>()(v.z()) << 1);
    }
};

struct PFNodeComparator {
    bool operator()(const PFNode* a, const PFNode* b) const {
        return a->fCost() > b->fCost();
    }
};

PFNode::PFNode(PFNode *parent, Vec3 position, float gCost, float hCost)
    : parent(parent), position(position), gCost(gCost), hCost(hCost)
{}
float PFNode::fCost() const { return gCost + hCost; }

bool Pathfinding::_isValid(const World *world, const Vec3 &pos)
{
    bool valid = world->IsPositionWalkable(pos);
    return valid;
}

float Pathfinding::_heuristic(const World *world, const Vec3 &a, const Vec3 &b)
{
    return std::abs(a.x() - b.x()) + std::abs(a.y() - b.y()) + std::abs(a.z() - b.z());
}

std::list<Vec3> Pathfinding::FindPath(const World *world, const Vec3 &start, const Vec3 &end, bool debug)
{
    if (!_isValid(world, end)) {
        if (debug) std::cout << "End point is invalid." << std::endl;
        return {};
    }

    std::unordered_map<Vec3, PFNode, Vec3Hasher> allNodes;
    std::unordered_set<Vec3, Vec3Hasher> closedSet;
    std::priority_queue<PFNode*, std::vector<PFNode*>, PFNodeComparator> openList;

    allNodes[start] = PFNode(nullptr, start, 0, _heuristic(world, start, end));
    openList.push(&allNodes[start]);

    while (!openList.empty()) {
        PFNode* currentNode = openList.top();
        openList.pop();

        if (closedSet.find(currentNode->position) != closedSet.end()) continue;
        closedSet.insert(currentNode->position);

        if (debug) std::cout << "Checking node: " << currentNode->position.ToString() << std::endl; // Debug

        if (currentNode->position == end) {
            std::list<Vec3> path;
            while (currentNode) {
                path.push_front(currentNode->position);
                currentNode = currentNode->parent;
            }
            return path;
        }

        std::vector<Vec3> neighbors;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {
                    neighbors.push_back(currentNode->position + Vec3(i, j, k));
                }
            }
        }

        for (const Vec3 &neighborPos : neighbors) {
            if (!_isValid(world, neighborPos)) {
                if (debug) std::cout << "Neighbor " << neighborPos.ToString() << " is not valid." << std::endl; // Debug
                continue;
            }
            if (closedSet.find(neighborPos) != closedSet.end()) {
                if (debug) std::cout << "Neighbor " << neighborPos.ToString() << " is in closed set." << std::endl; // Debug
                continue;
            }

            float movementCost = 1;  // default movement cost

            // Check if movement is diagonal
            if (
                (neighborPos.x() != currentNode->position.x() && neighborPos.y() != currentNode->position.y()) ||
                (neighborPos.x() != currentNode->position.x() && neighborPos.z() != currentNode->position.z()) ||
                (neighborPos.y() != currentNode->position.y() && neighborPos.z() != currentNode->position.z())
            ) {
                movementCost = 1.414;
            }

            if (neighborPos.z() > currentNode->position.z() &&
            (neighborPos.x() != currentNode->position.x() || neighborPos.y() != currentNode->position.y())) {
                movementCost *= 1.5;  // Upward diagonals cost more
            }

            float tentativeGCost = currentNode->gCost + movementCost;

            if (allNodes.find(neighborPos) == allNodes.end() || tentativeGCost < allNodes[neighborPos].gCost) {
                allNodes[neighborPos] = PFNode(currentNode, neighborPos, tentativeGCost, _heuristic(world, neighborPos, end));
                openList.push(&allNodes[neighborPos]);
            }
        }
    }

    if (debug) std::cout << "No valid path found." << std::endl;
    return {};
}
