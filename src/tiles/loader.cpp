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

    std::vector<Vec2> spritePositions;
    std::vector<Color> spriteColors;

    // Extract sprite positions
    tinyxml2::XMLElement *spriteElem = tileElem->FirstChildElement("SPRITE");
    while (spriteElem != nullptr) {
        spritePositions.push_back(Vec2(spriteElem->IntAttribute("x"), spriteElem->IntAttribute("y")));
        spriteElem = spriteElem->NextSiblingElement("SPRITE");
    }

    // Extract sprite colors
    tinyxml2::XMLElement *colorElem = tileElem->FirstChildElement("COLOR");
    while (colorElem != nullptr) {
        spriteColors.push_back(Color(colorElem->IntAttribute("r"), colorElem->IntAttribute("g"), colorElem->IntAttribute("b")));
        colorElem = colorElem->NextSiblingElement("COLOR");
    }

    // Combine sprite positions and colors and store them
    for (const Vec2 &pos : spritePositions) {
        for (const Color &col : spriteColors) {
            tileType->AddSpriteVariant(SpriteVariant(pos, col));
        }
    }

    return tileType;
}
