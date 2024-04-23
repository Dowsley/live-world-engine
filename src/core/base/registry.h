#pragma once

#include <unordered_map>
#include <string>
#include <vector>

template <typename T, typename L>
class BaseRegistry {
public:
    explicit BaseRegistry(const std::string &path)
            : loader(path) {
        // Do not call _load() here
    }

    virtual ~BaseRegistry() {
        for (auto & type : types) {
            delete type.second;
        }
    }

    void Reload() {
        types.clear();
        _load();
    }

    void Initialize() {
        _load();
    }

    T* GetTypeById(const std::string &id) const {
        auto it = types.find(id);
        if (it != types.end()) {
            return it->second;
        }
        return nullptr;
    }

    std::vector<const T*> GetAllTypes() const {
        std::vector<const T*> vec;
        for (const auto& pair : types) {
            vec.push_back(pair.second);
        }
        return vec;
    }

protected:
    void _load() {
        for (const auto & type : _loadSpecific()) {
            types[type->GetID()] = type;
        }
    }

    virtual std::vector<T*> _loadSpecific() = 0;

    L loader;
    std::unordered_map<std::string, T*> types;
};
