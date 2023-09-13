#include "registry.h"

template <typename T, typename L>
BaseRegistry<T, L>::BaseRegistry(const std::string &path)
: loader(path) {
    // Do not call _load() here
}

template <typename T, typename L>
BaseRegistry<T, L>::~BaseRegistry() {
    for (auto & type : types) {
        delete type.second;
    }
}

template <typename T, typename L>
T* BaseRegistry<T, L>::GetTypeById(const std::string &id) const {
    auto it = types.find(id);
    if (it != types.end()) {
        return it->second;
    }
    return nullptr;
}

template <typename T, typename L>
void BaseRegistry<T, L>::Reload() {
    types.clear();
    _load();
}

template <typename T, typename L>
void BaseRegistry<T, L>::Initialize() {
    _load();
}

template <typename T, typename L>
void BaseRegistry<T, L>::_load() {
    for (const auto & type : _loadSpecific()) {
        types[type->GetID()] = type;
    }
}
