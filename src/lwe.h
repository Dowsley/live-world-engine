#pragma once

#define OLC_PGE_APPLICATION

#include <string>

#if _WIN32
	#define REL_PATH_FOR_OS "assets\\tileset\\urizen.png"
#else
	#define REL_PATH_FOR_OS "assets/tileset/urizen.png"
#endif

#include "engine/olcPixelGameEngine.h"

#include "core/index.h"
#include "tiles/index.h"
#include "creatures/index.h"
#include "utils/index.h"
#include "structures/index.h"
#include "lib/index.h"

class LiveWorldEngine : public olc::PixelGameEngine
{
public:
    LiveWorldEngine();

private:
    // Note: If the game is mostly black and blue, then the path to the tileset is wrong.
    olc::Sprite tileSet{REL_PATH_FOR_OS};
    World world{Settings::WORLD_DIMENSIONS};

    struct {
        float posX = 0.0f;
        float posY = 0.0f;
        int speedMultiplier = 1;
    } camera;

    struct {
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;
    } moveInput;

    bool paused = false;
    int currDepth = 20;
    unsigned int tickTimer = 0;

    void _handleInputs();
    void _moveCamera(float fElapsedTime);
    void _simulate(float fElapsedTime);
    void _drawWorld();
    void _drawTile(const Vec3 &pos);

protected:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
};