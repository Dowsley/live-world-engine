#include "../lib/tinyxml2.h"

#include "loader.h"

using namespace tinyxml2;

TileType* TileLoader::_loadSpecific(const std::string &tileFile) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(tileFile.c_str()) != tinyxml2::XML_SUCCESS) {
        std::string errorString = doc.ErrorStr(); 
        throw std::runtime_error("Failed to load tile file: " + tileFile + ". Error: " + errorString);
    }

    /* General Info  */
    TileType *tileType = new TileType();
    tinyxml2::XMLElement *tileElem = doc.FirstChildElement("TILE");
    tileType
        ->SetID(tileElem->Attribute("id"))
        ->SetDescription(tileElem->FirstChildElement("DESCRIPTION")->GetText())
        ->SetMaxHealth(tileElem->FirstChildElement("MAX_HEALTH")->IntText())
        ->SetName(tileElem->FirstChildElement("NAME")->Attribute("singular"));
    
    if (tileElem->FirstChildElement("SOLID") != nullptr) {
        tileType->SetIsSolid();
    }

    /* Sprite positions */
    tinyxml2::XMLElement* spriteElem = tileElem->FirstChildElement("SPRITE");
    while (spriteElem != nullptr) {
        tileType->AddSpritePosVariant(
            Vec2(spriteElem->IntAttribute("x"), spriteElem->IntAttribute("y"))
        );
        
        // Move to the next <SPRITE /> element
        spriteElem = spriteElem->NextSiblingElement("SPRITE");
    }

    /* Colors */
    tinyxml2::XMLElement* colorElem = tileElem->FirstChildElement("COLOR");
    while (colorElem != nullptr) {
        tileType->AddSpriteColorVariant(
            Color(
                colorElem->IntAttribute("r"),
                colorElem->IntAttribute("g"),
                colorElem->IntAttribute("b")
            )
        );
        
        // Move to the next <COLOR /> element
        colorElem = colorElem->NextSiblingElement("COLOR");
    }

    return tileType;
}
