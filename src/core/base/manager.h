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
    explicit ManagerBase(World *world) : worldRef(world) {}

    virtual ~ManagerBase() {
        ClearItems();
    }

    T* GetItemAt(const Vec3 &pos) const {
        int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
        auto it = items.find(index);
        return (it != items.end()) ? it->second : nullptr;
    }

    void TraverseItems(std::function<void(T*)> callback) {
        for (auto& item : items) {
            callback(item.second);
        }
    }

    int GetTotalItemCount() const {
        return items.size();
    }

    void ClearItems() {
        for (auto& item : items) {
            delete item.second;
            item.second = nullptr;
        }
        items.clear();
    }
};
