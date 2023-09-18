#include <filesystem>

#include "loader.h"

template<typename T>
std::vector<T*> BaseLoader<T>::LoadAll() {
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
