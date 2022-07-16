#define OLC_PGE_APPLICATION
#include "../engine/olcPixelGameEngine.h"
#include "Map/Map.cpp"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Rogue : public olc::PixelGameEngine {
    public:
		Rogue() {
			sAppName = "Rogue";
		}
		
    private:
		Map *map = new Map(1024, 512); 

		float fCameraPosX = 0.0f;
		float fCameraPosY = 0.0f;

		void DrawMap()
		{
			unsigned char tile;
			for (int y = 0; y < ScreenHeight(); y++) {
				for (int x = 0; x < ScreenWidth(); x++) {
					tile = map->GetTile(x + (int)fCameraPosX, y + (int)fCameraPosY);
					// printf("%d\n", (int)tile);
					Draw(x, y, olc::Pixel(tile, tile, tile));
				}
			}
		}

    protected:
		bool OnUserCreate() override
		{
			map->GenerateMap();
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			// Press 'M' key to regenerate map
			if (GetKey(olc::Key::M).bReleased) {
				map->GenerateMap();
			}

			// Mouse Edge Map Scroll
			float fMapScrollSpeed = 400.0f;

			// if (GetMouseX() < 5)
			if (GetKey(olc::Key::LEFT).bHeld)
				fCameraPosX -= fMapScrollSpeed * fElapsedTime;
			// if (GetMouseX() > ScreenWidth() - 5)
			if (GetKey(olc::Key::RIGHT).bHeld)
				fCameraPosX += fMapScrollSpeed * fElapsedTime;
			// if (GetMouseY() < 5)
			if (GetKey(olc::Key::UP).bHeld)
				fCameraPosY -= fMapScrollSpeed * fElapsedTime;
			// if (GetMouseY() > ScreenHeight() - 5)
			if (GetKey(olc::Key::DOWN).bHeld)
				fCameraPosY += fMapScrollSpeed * fElapsedTime;

			// Clamp map boundaries
			if (fCameraPosX < 0) fCameraPosX = 0;
			if (fCameraPosX >= map->GetWidth() - ScreenWidth()) fCameraPosX = map->GetWidth() - ScreenWidth();
			if (fCameraPosY < 0) fCameraPosY = 0;
			if (fCameraPosY >= map->GetHeight() - ScreenHeight()) fCameraPosY = map->GetHeight() - ScreenHeight();

			DrawMap();

			return true;
		}

	};


	int main(int argc, char const *argv[]) {
		Rogue game;
			game.Construct(256, 160, 6, 6);
			// game.Construct(1024, 512, 1, 1);
			game.Start();

		return 0;
	}
