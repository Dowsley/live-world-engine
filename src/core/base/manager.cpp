#include "manager.h"

template <typename T>
ManagerBase<T>::ManagerBase(World *world) : worldRef(world) {}

template <typename T>
ManagerBase<T>::~ManagerBase() {
    for (auto& pair : items) {
        delete pair.second;
    }
}

template <typename T>
T* ManagerBase<T>::GetItemAt(const Vec3 &pos) const {
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    if(items.find(index) != items.end()) {
        return items.at(index);
    }
    return nullptr;
}

template <typename T>
void ManagerBase<T>::TraverseItems(std::function<void(T*)> callback) {
    for (auto& pair : items) {
        callback(pair.second);
    }
}

template <typename T>
int ManagerBase<T>::GetTotalItemCount() const {
    return items.size();
}

template <typename T>
void ManagerBase<T>::ClearItems() {
    items.clear();
}
