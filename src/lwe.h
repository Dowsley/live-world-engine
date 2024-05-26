#pragma once

#define OLC_PGE_APPLICATION

#include <string>

#if _WIN32
	#define REL_PATH_FOR_OS "assets\\tileset\\urizen_onebit_tileset__v1d0_colored.png"
#else
	#define REL_PATH_FOR_OS "assets/tileset/urizen_onebit_tileset__v1d0_colored.png"
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

    struct MoveInput {
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;
    } moveInput;

    struct {
        Vec2 pointerPos;
        Vec2 pointerSpritePos = Vec2(96, 49);
        bool active = false;
        bool pointerBlink = true;
        Color color = olc::YELLOW;
        float accumulatedTime = 0.0f;
        const float BLINK_INTERVAL = 0.35f;
        struct MoveInput moveInput;
        Vec3 start;
        Vec3 end;
        std::list<Vec3> path;
        int tracePath = 0;
    } viewMode;

    bool paused = false;
    int currDepth = 20;
    unsigned int tickTimer = 0;

    void _handleInputs();
    void _moveCamera(float fElapsedTime);
    void _simulate(float fElapsedTime);
    bool _updateUI(float fElapsedTime);
    void _drawWorld();
    void _drawTile(const Vec2 &pos, const Color &color, const Vec2 &spritePos);

protected:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
};
