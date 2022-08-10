#include "../../engine/olcPixelGameEngine.h"

class Tile {
public:
    virtual int Update() = 0;
    virtual olc::Pixel GetRepresentation()
    {
        return NULL;
    }
};
