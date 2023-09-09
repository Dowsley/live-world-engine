#include "lwe.h"

LiveWorldEngine::LiveWorldEngine() {
    sAppName = "Live World Engine";
}

void LiveWorldEngine::_drawWorld()
{
    Clear(olc::BLACK);

    int trueX, trueY, trueZ;

    bool isCurrTileEmpty;
    bool isLowerTileEmpty;
    bool isLowerTileSurface;
    bool isCurrTileOccupiedByCreature;
    for (int y = 0; y < (ScreenHeight() / Settings::TILE_SIZE.y); y++) {
        for (int x = 0; x < (ScreenWidth() / Settings::TILE_SIZE.x); x++) {
            trueX = x + (int) camera.posX;
            trueY = y + (int) camera.posY;

            isCurrTileEmpty = world.GetTileTypeName(trueX, trueY, currDepth) == "empty";
            isCurrTileOccupiedByCreature = world.IsThereCreatureAt(trueX, trueY, currDepth);
            isLowerTileEmpty = world.GetTileTypeName(trueX, trueY, currDepth+1) == "empty";
            isLowerTileSurface = world.GetTileType(trueX, trueY, currDepth+1)->isSurface;
            if (isCurrTileEmpty && !isCurrTileOccupiedByCreature && !isLowerTileEmpty && isLowerTileSurface) {
                trueZ = currDepth + 1;
            } else {
                trueZ = currDepth;
            }
            _drawTile(x, y, trueZ);
        }
    }
    std::string str = "Layer: ";
    str.append(std::to_string(currDepth));
    DrawString(Vec2(0,0), str, olc::WHITE, 1);
}

void LiveWorldEngine::_drawTile(int x, int y, int z)
{
    int currX = x + (int)camera.posX;
    int currY = y + (int)camera.posY;

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

void LiveWorldEngine::_handleInputs()
{
    camera.speedMultiplier = 1;

    // Press 'M' key to regenerate world
    if (GetKey(olc::Key::M).bReleased) {
        world.Generate();
    }

    // Hold 'Z' key to move camera faster
    if (GetKey(olc::Key::Z).bHeld) {
        camera.speedMultiplier = 4;
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

    // Camera movement
    moveInput.left = GetKey(olc::Key::LEFT).bHeld;
    moveInput.right = GetKey(olc::Key::RIGHT).bHeld;
    moveInput.up = GetKey(olc::Key::UP).bHeld;
    moveInput.down = GetKey(olc::Key::DOWN).bHeld;
}

void LiveWorldEngine::_moveCamera(float fElapsedTime)
{
    // Mouse Edge Map Scroll
    float mapScrollSpeed = 100.0f * camera.speedMultiplier;

    if (moveInput.left)
        camera.posX -= mapScrollSpeed * fElapsedTime;
    if (moveInput.right)
        camera.posX += mapScrollSpeed * fElapsedTime;
    if (moveInput.up)
        camera.posY -= mapScrollSpeed * fElapsedTime;
    if (moveInput.down)
        camera.posY += mapScrollSpeed * fElapsedTime;

    // Clamp world boundaries
    if (camera.posX < 0)
        camera.posX = 0;
    if (camera.posX >= world.GetWidth() - ScreenWidth())
        camera.posX = world.GetWidth() - ScreenWidth();
    if (camera.posY < 0)
        camera.posY = 0;
    if (camera.posY >= world.GetHeight() - ScreenHeight())
        camera.posY = world.GetHeight() - ScreenHeight();
}

void LiveWorldEngine::_simulate(float fElapsedTime)
{
    if (!paused) {
        tickTimer += fElapsedTime * 1000;
        if (tickTimer >= Settings::TICK_DURATION) {
            world.Update();
            tickTimer = tickTimer - Settings::TICK_DURATION;
        }
    }
}


bool LiveWorldEngine::OnUserCreate()
{
    world.Generate();
    _drawWorld();

    return true;
}

bool LiveWorldEngine::OnUserUpdate(float fElapsedTime)
{
    _handleInputs();
    _moveCamera(fElapsedTime);
    _simulate(fElapsedTime);
    _drawWorld();

    return true;
}