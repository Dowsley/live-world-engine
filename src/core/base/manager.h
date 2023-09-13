#pragma once

#include <unordered_map>
#include <functional>

#include "../../structures/vec3.h"
#include "../../utils/geometry.h"

class World;

template <typename T>
class ManagerBase {
protected:
    World *worldRef = nullptr;
    std::unordered_map<int, T*> items;

public:
    ManagerBase(World *world);
    virtual ~ManagerBase();

    T* GetItemAt(const Vec3 &pos) const;
    void TraverseItems(std::function<void(T*)> callback);
    int GetTotalItemCount() const;
    void ClearItems();
};
