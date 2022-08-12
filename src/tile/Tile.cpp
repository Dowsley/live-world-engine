#include "../../engine/olcPixelGameEngine.h"

class Tile {
public:
    virtual int Update() = 0;
    virtual olc::Pixel GetColor() = 0;
    virtual olc::vi2d GetRepresentation() = 0;
};
