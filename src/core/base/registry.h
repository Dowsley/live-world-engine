#pragma once

#include <unordered_map>
#include <string>
#include <vector>

template <typename T, typename L>
class BaseRegistry {
public:
    explicit BaseRegistry(const std::string &path);
    virtual ~BaseRegistry();

    void Reload();
    void Initialize();

    T* GetTypeById(const std::string &id) const;
    std::vector<const T*> GetAllTypes() const; 

protected:
    void _load();
    virtual std::vector<T*> _loadSpecific() = 0;

    L loader;
    std::unordered_map<std::string, T*> types;
};
