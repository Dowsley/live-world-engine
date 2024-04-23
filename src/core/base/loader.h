#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

template<typename T>
class BaseLoader {
public:
    explicit BaseLoader(const std::string &path) : directoryPath(path) {}

    virtual ~BaseLoader() {}

    std::vector<T*> LoadAll() {
        std::vector<T*> types;
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
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
