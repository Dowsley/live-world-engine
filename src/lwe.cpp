#include "lwe.h"

LiveWorldEngine::LiveWorldEngine() {
    sAppName = "Live World Engine";
    viewMode.pointerPos = Vec2(
        ((ScreenWidth() / Settings::TILE_SIZE.x) / 2) + 2,
        ((ScreenHeight() / Settings::TILE_SIZE.y) / 2) - 2
    );
}

void LiveWorldEngine::_drawWorld()
{
    Clear(olc::BLACK);
    for (int y = 0; y < (ScreenHeight() / Settings::TILE_SIZE.y); y++) {
        for (int x = 0; x < (ScreenWidth() / Settings::TILE_SIZE.x); x++) {
            int mapX = x + (int) camera.posX;
            int mapY = y + (int) camera.posY;

            bool isPointerPos = viewMode.pointerPos.x == x && viewMode.pointerPos.y == y;
            bool isPath = false;
            if (viewMode.tracePath == 2) {
                for (auto & p : viewMode.path) {
                    isPath = p.x() == mapX && p.y() == mapY && p.z() == currDepth;
                    if (isPath) {
                        break;
                    }
                }
            }
            if (viewMode.active && viewMode.pointerBlink && (isPointerPos || isPath)) {
                _drawTile(
                        Vec2(x, y),
                        viewMode.color,
                        viewMode.pointerSpritePos
                );
            } else {
                bool isLastLayer = currDepth == Settings::WORLD_DIMENSIONS.depth() - 1;
                Vec3 currTilePos = Vec3(mapX, mapY, currDepth);
                Vec3 lowerTilePos = Vec3(mapX, mapY, currDepth + 1);
                bool isCurrTileEmpty = world.IsPositionEmpty(currTilePos);
                bool isLowerTileEmpty = isLastLayer || world.IsPositionEmpty(lowerTilePos);
                bool isLowerTileSolid = !isLastLayer && world.GetTypeForTileAt(lowerTilePos)->GetIsSolid();
                int mapZ = currDepth;
                if (isCurrTileEmpty && !isLowerTileEmpty && isLowerTileSolid) {
                    mapZ += 1;
                }
                _drawTile(
                    Vec2(x, y),
                    world.GetTileColor(Vec3(mapX, mapY, mapZ)),
                    world.GetTileSprite(Vec3(mapX, mapY, mapZ))
                );
            }
        }
    }
    std::string str = "Layer: ";
    str.append(std::to_string(currDepth));
    DrawString(Vec2(0, 0), str, olc::WHITE, 1);
    DrawString(Vec2(0, 10), paused ? "Paused" : "Active", olc::WHITE, 1);

    if (viewMode.active) {
        Vec3 viewPosMap = Vec3(
            viewMode.pointerPos.x + (int) camera.posX,
            viewMode.pointerPos.y + (int) camera.posY,
            currDepth
        );
        std::string tileID = world.GetTypeIDForTileAt(viewPosMap);
        std::string creatureID = world.GetTypeIDForCreatureAt(viewPosMap);
        DrawString(
            Vec2(0, 20),
            viewPosMap.ToString() + ": T: '" + tileID + "', C: '" + creatureID + "'",
            olc::WHITE, 1
        );
        str = "PATH: ";
        if (viewMode.tracePath == 0) {
            str += "Press ENTER";
        } else if (viewMode.tracePath == 1) {
            str += "From " + viewMode.start.ToString();
        } else {
            str += "From " + viewMode.start.ToString() + " To " + viewMode.end.ToString();
        }

        DrawString(
            Vec2(0, 30),
            str,
            olc::WHITE, 1
        );
    }
}

void LiveWorldEngine::_drawTile(const Vec2 &pos, const Color &color, const Vec2 &spritePos)
{
    int x = pos.x;
    int y = pos.y;

    Vec2 realSpritePos = spritePos * Settings::TILE_SIZE + (Settings::TILE_OFFSET * spritePos) + Vec2(1,1);

    Color ref;
    Vec2 screenPos;
    for (int i = 0; i < Settings::TILE_SIZE.y; i++) {
        for (int j = 0; j < Settings::TILE_SIZE.x; j++) {
            screenPos = Vec2((x * Settings::TILE_SIZE.x) + j, (y * Settings::TILE_SIZE.y) + i);
            ref = tileSet.GetPixel(j + realSpritePos.x, i + realSpritePos.y);
            if (ref != Settings::BACK_PLACEHOLDER) {
                Draw(screenPos, color);
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
        if (currDepth != Settings::WORLD_DIMENSIONS.depth() - 1) {
            currDepth += 1;
        }
    }

    // Press 'C' key to ascend depth
    if (GetKey(olc::Key::C).bReleased) {
        if (currDepth != 0) {
            currDepth -= 1;
        }
    }

    // Press 'SPACE' key to toggle pause simulation
    if (GetKey(olc::Key::SPACE).bReleased) {
        paused = !paused;
    }

    // Press 'K' key to toggle view mode
    if (GetKey(olc::Key::K).bReleased) {
        viewMode.active = !viewMode.active;
    }

    // Camera movement
    moveInput.left = GetKey(olc::Key::LEFT).bHeld;
    moveInput.right = GetKey(olc::Key::RIGHT).bHeld;
    moveInput.up = GetKey(olc::Key::UP).bHeld;
    moveInput.down = GetKey(olc::Key::DOWN).bHeld;

    // View Mode
    viewMode.moveInput.left = GetKey(olc::Key::LEFT).bReleased;
    viewMode.moveInput.right = GetKey(olc::Key::RIGHT).bReleased;
    viewMode.moveInput.up = GetKey(olc::Key::UP).bReleased;
    viewMode.moveInput.down = GetKey(olc::Key::DOWN).bReleased;

    if (GetKey(olc::Key::ENTER).bReleased && viewMode.active) {
        if (viewMode.tracePath == 0) {
            viewMode.start = Vec3(
                viewMode.pointerPos.x + (int) camera.posX,
                viewMode.pointerPos.y + (int) camera.posY,
                currDepth
            );
            viewMode.tracePath = 1;
        } else if (viewMode.tracePath == 1) {
            viewMode.tracePath = 2;
            viewMode.end = Vec3(
                viewMode.pointerPos.x + (int) camera.posX,
                viewMode.pointerPos.y + (int) camera.posY,
                currDepth
            );
            viewMode.path = world.GetPath(
                viewMode.start,
                viewMode.end
            );
            printf("%zu\n", viewMode.path.size());
            for (auto & p : viewMode.path) {
                std::cout << p.ToString() << std::endl;
            }
        }
    }
    if (GetKey(olc::Key::ESCAPE).bReleased && viewMode.tracePath) {
        viewMode.tracePath = 0;
    }
}

void LiveWorldEngine::_moveCamera(float fElapsedTime)
{
    if (viewMode.active) {
        if (viewMode.moveInput.left) {
            viewMode.pointerPos.x -= 1;
        }
        if (viewMode.moveInput.right) {
            viewMode.pointerPos.x += 1;
        }
        if (viewMode.moveInput.up) {
            viewMode.pointerPos.y -= 1;
        }
        if (viewMode.moveInput.down) {
            viewMode.pointerPos.y += 1;
        }

        // Clamp screen grid boundaries
        int gridWidth = (ScreenWidth() / Settings::TILE_SIZE.x);
        int gridHeight = (ScreenHeight() / Settings::TILE_SIZE.y);
        if (viewMode.pointerPos.x < 0)
            viewMode.pointerPos.x = 0;
        if (viewMode.pointerPos.x >= gridWidth)
            viewMode.pointerPos.x = gridWidth - 1;
        if (viewMode.pointerPos.y < 0)
            viewMode.pointerPos.y = 0;
        if (viewMode.pointerPos.y >= gridHeight)
            viewMode.pointerPos.y = gridHeight - 1;
    } else {
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


bool LiveWorldEngine::_updateUI(float fElapsedTime)
{
    viewMode.accumulatedTime += fElapsedTime;
    if (viewMode.accumulatedTime > viewMode.BLINK_INTERVAL) {
        viewMode.pointerBlink = !viewMode.pointerBlink;
        viewMode.accumulatedTime -= viewMode.BLINK_INTERVAL;
    }

    return true;
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
    _updateUI(fElapsedTime);
    _drawWorld();

    return true;
}
