#pragma once

#include <string>
#include <vector>

template<typename T>
class BaseLoader {
public:
    explicit BaseLoader(const std::string &path) : directoryPath(path) {}

    std::vector<T*> LoadAll();

protected:
    virtual T* _loadSpecific(const std::string &file) = 0;
    std::string directoryPath;
};
