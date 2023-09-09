#include <filesystem>

#include "loader.h"

using namespace tinyxml2;

CreatureLoader::CreatureLoader(const std::string& path) : directoryPath(path) {}

std::vector<CreatureType*> CreatureLoader::LoadAllCreatures() {
    std::vector<CreatureType*> creatureTypes;
    for (const auto & entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".xml") {
            creatureTypes.push_back(_loadCreature(entry.path().string()));
        }
    }
    return creatureTypes;
}

CreatureType* CreatureLoader::_loadCreature(const std::string &creatureFile) {
    CreatureType *creatureType = new CreatureType();

    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(creatureFile.c_str()) != tinyxml2::XML_SUCCESS) {
        std::string errorString = doc.ErrorStr(); // Get the error string from tinyxml2
        throw std::runtime_error("Failed to load creature file: " + creatureFile + ". Error: " + errorString);
        return creatureType;
    }

    tinyxml2::XMLElement *creatureElem = doc.FirstChildElement("CREATURE");
    if (creatureElem) {
        creatureType
            ->SetId(creatureElem->Attribute("id"))
            ->SetDescription(creatureElem->FirstChildElement("DESCRIPTION")->GetText())
            ->SetSpawnChance(creatureElem->FirstChildElement("SPAWN_CHANCE")->IntText())
            ->SetName(creatureElem->FirstChildElement("NAME")->Attribute("singular"));

        tinyxml2::XMLElement *spriteElem = creatureElem->FirstChildElement("SPRITE");
        
        tinyxml2::XMLElement *spritePosElem = spriteElem->FirstChildElement("POSITION");
        creatureType->SetSpritePos(
            Vec2(spritePosElem->IntAttribute("x"), spritePosElem->IntAttribute("y"))
        );

        tinyxml2::XMLElement *spriteColorElem = spriteElem->FirstChildElement("COLOR");
        creatureType
            ->SetSpriteColor(
                Color(
                    spriteColorElem->IntAttribute("r"),
                    spriteColorElem->IntAttribute("g"),
                    spriteColorElem->IntAttribute("b")
                )
        );
    }

    return creatureType;
}
