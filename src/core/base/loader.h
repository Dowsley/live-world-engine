#pragma once

#include <string>
#include <utility>
#include <vector>
#include <filesystem>
#include <iostream>

template<typename T>
class BaseLoader {
public:
    explicit BaseLoader(std::string path) : directoryPath(std::move(path)) {}

    virtual ~BaseLoader() = default;

    std::vector<T*> LoadAll() {
        std::vector<T*> types;
        for (const auto & entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.path().extension() == ".xml") {
                T *loaded = _loadSpecific(entry.path().string());
                std::cout << "Loaded: " << loaded->GetID() << std::endl;
                types.push_back(loaded);
            }
        }
        return types;
    }

protected:
    virtual T* _loadSpecific(const std::string &file) = 0;
    std::string directoryPath;
};
