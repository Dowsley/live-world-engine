#define OLC_PGE_APPLICATION

#if _WIN32
    #define REL_PATH_FOR_OS "assets\\tileset\\urizen.png"
#else
    #define REL_PATH_FOR_OS "assets/tileset/urizen.png"
#endif

#include <string>

#include "engine/olcPixelGameEngine.h"

#include "core/index.cpp"
#include "tiles/index.cpp"
#include "creatures/index.cpp"
#include "utils/index.cpp"
#include "structures/index.cpp"
#include "lib/index.cpp"

class LiveWorldEngine : public olc::PixelGameEngine
{
public:
    LiveWorldEngine() {
        sAppName = "Live World Engine";
    }

private:
    olc::Sprite tileSet = olc::Sprite(REL_PATH_FOR_OS); // Note: You need to define REL_PATH_FOR_OS elsewhere, probably in a config or main header
    World world = World(Settings::WORLD_DIMENSIONS);
    
    bool paused = true;

    float cameraPosX = 0.0f;
    float cameraPosY = 0.0f;

    int currDepth = 20;
    unsigned int _tickTimer = 0;

    void LogColor(const Color &p)
    {
        printf("R: %d, G: %d, B:%d\n", p.r, p.g, p.b);
    }

    void DrawWorld()
    {
        Clear(olc::BLACK);

        int trueX, trueY, trueZ;

        bool isCurrTileEmpty;
        bool isLowerTileEmpty;
        bool isLowerTileSurface;
        bool isCurrTileOccupiedByCreature;
        for (int y = 0; y < (ScreenHeight() / Settings::TILE_SIZE.y); y++) {
            for (int x = 0; x < (ScreenWidth() / Settings::TILE_SIZE.x); x++) {
                trueX = x + (int) cameraPosX;
                trueY = y + (int) cameraPosY;

                isCurrTileEmpty = world.GetTileTypeName(trueX, trueY, currDepth) == "empty";
                isCurrTileOccupiedByCreature = world.IsThereCreatureAt(trueX, trueY, currDepth);
                isLowerTileEmpty = world.GetTileTypeName(trueX, trueY, currDepth+1) == "empty";
                isLowerTileSurface = world.GetTileType(trueX, trueY, currDepth+1)->isSurface;
                if (isCurrTileEmpty && !isCurrTileOccupiedByCreature && !isLowerTileEmpty && isLowerTileSurface) {
                    trueZ = currDepth + 1;
                } else {
                    trueZ = currDepth;
                }
                DrawTile(x, y, trueZ);
            }
        }
        std::string str = "Layer: ";
        str.append(std::to_string(currDepth));
        DrawString(Vec2(0,0), str, olc::WHITE, 1);
    }

    void DrawTile(int x, int y, int z)
    {
        int currX = x + (int)cameraPosX;
        int currY = y + (int)cameraPosY;

        Color foreColor = world.GetTileForeColor(currX, currY, z);
        Color backColor = world.GetTileBackColor(currX, currY, z);
        Vec2 spritePos = world.GetTileSprite(currX, currY, z);

        bool tmp = world.IsThereCreatureAt(currX, currY, z);

        spritePos = spritePos * Settings::TILE_SIZE + (Settings::TILE_OFFSET * spritePos) + Vec2(1,1);

        Color ref;
        Vec2 screenPos;
        for (int i = 0; i < Settings::TILE_SIZE.y; i++) {
            for (int j = 0; j < Settings::TILE_SIZE.x; j++) {
                screenPos = Vec2((x * Settings::TILE_SIZE.x) + j, (y * Settings::TILE_SIZE.y) + i);
                ref = tileSet.GetPixel(j + spritePos.x, i + spritePos.y);
                if (ref == Settings::FORE_PLACEHOLDER) {
                    Draw(screenPos, foreColor);
                }
                else {
                    Draw(screenPos, ref);
                }
            }
        }
    }

protected:
    bool OnUserCreate() override
    {
        world.Generate();
        DrawWorld();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // Press 'M' key to regenerate world
        if (GetKey(olc::Key::M).bReleased) {
            world.Generate();
        }

        // // Press 'R' key to update entities
        // if (GetKey(olc::Key::R).bReleased) {
        // 	redraw = true;
        // }

        // Hold 'Z' key to move camera faster
        int mode = 1;
        if (GetKey(olc::Key::Z).bHeld) {
            mode = 4;
        }

        // Press 'X' key to descend depth
        if (GetKey(olc::Key::X).bReleased) {
            if (currDepth != Settings::WORLD_DIMENSIONS.z() - 1) {
                currDepth += 1;
            }
        }

        // Press 'C' key to ascend depth
        if (GetKey(olc::Key::C).bReleased) {
            if (currDepth != 0) {
                currDepth -= 1;
            }
        }

        // Press 'P' key to pause simulation
        if (GetKey(olc::Key::P).bReleased) {
            paused = !paused;
        }

        // Mouse Edge Map Scroll
        float mapScrollSpeed = 100.0f * mode;

        bool left = GetKey(olc::Key::LEFT).bHeld;
        bool right = GetKey(olc::Key::RIGHT).bHeld;
        bool up = GetKey(olc::Key::UP).bHeld;
        bool down = GetKey(olc::Key::DOWN).bHeld;

        if (left)
            cameraPosX -= mapScrollSpeed * fElapsedTime;
        if (right)
            cameraPosX += mapScrollSpeed * fElapsedTime;
        if (up)
            cameraPosY -= mapScrollSpeed * fElapsedTime;
        if (down)
            cameraPosY += mapScrollSpeed * fElapsedTime;

        // Clamp world boundaries
        if (cameraPosX < 0)
            cameraPosX = 0;
        if (cameraPosX >= world.GetWidth() - ScreenWidth())
            cameraPosX = world.GetWidth() - ScreenWidth();
        if (cameraPosY < 0)
            cameraPosY = 0;
        if (cameraPosY >= world.GetHeight() - ScreenHeight())
            cameraPosY = world.GetHeight() - ScreenHeight();

        if (!paused) {
            _tickTimer += fElapsedTime * 1000;
            if (_tickTimer >= Settings::TICK_DURATION) {
                world.Update();
                _tickTimer = _tickTimer - Settings::TICK_DURATION;
            }
        }
        DrawWorld();

        return true;
    }

};


int main(int argc, char const *argv[])
{
    LiveWorldEngine game;

    game.Construct(312, 204, 4, 4);
    game.Start();

    return 0;
}
