#pragma once

#include <functional>
#include "../../structures/vec3.h"

class World;

template <typename T>
class ManagerBase {
protected:
    World* worldRef = nullptr;

public:
    explicit ManagerBase(World* world) : worldRef(world) {}
    virtual ~ManagerBase() = 0; // Virtual destructor to ensure proper cleanup

    virtual T* GetItemAt(const Vec3& pos) const = 0;
    virtual void TraverseItems(std::function<void(T*)> callback) = 0;
    [[nodiscard]] virtual int GetTotalItemCount() const = 0;
    virtual void ClearItems() = 0;
};

template <typename T>
ManagerBase<T>::~ManagerBase() = default; // Definition of the virtual destructor
