#include "../lib/tinyxml2.h"

#include "loader.h"

using namespace tinyxml2;

CreatureType* CreatureLoader::_loadSpecific(const std::string &creatureFile) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(creatureFile.c_str()) != tinyxml2::XML_SUCCESS) {
        std::string errorString = doc.ErrorStr(); 
        throw std::runtime_error("Failed to load creature file: " + creatureFile + ". Error: " + errorString);
    }

    /* General Info */
    CreatureType *creatureType = new CreatureType();
    tinyxml2::XMLElement *creatureElem = doc.FirstChildElement("CREATURE");
    creatureType
        ->SetID(creatureElem->Attribute("id"))
        ->SetDescription(creatureElem->FirstChildElement("DESCRIPTION")->GetText())
        ->SetSpawnChance(creatureElem->FirstChildElement("SPAWN_CHANCE")->IntText())
        ->SetName(creatureElem->FirstChildElement("NAME")->Attribute("singular"));

    /* Sprite and colors */
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

    return creatureType;
}
