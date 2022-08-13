#define OLC_PGE_APPLICATION
#include "../engine/olcPixelGameEngine.h"
#include "map/Map.cpp"
#include <string>

#define MAX_DEPTH 50

using namespace std;

class MarsSimulator : public olc::PixelGameEngine {
    public:
		MarsSimulator() {
			sAppName = "Mars Simulator";
		}

    private:
		olc::vi2d nTileSize;
		olc::Sprite *tileSet = new olc::Sprite("../assets/tileset/vanilla.png");
		// olc::Sprite *tileSet = new olc::Sprite("../assets/tileset/madmonkey/20x20_text.png");

		Map *map = new Map(1024, 512, MAX_DEPTH);

		float fCameraPosX = 0.0f;
		float fCameraPosY = 0.0f;

		int currDepth = 21;

		void DrawTile(int x, int y, int z)
		{
			olc::Pixel tileColor = map->GetTileColor(
				x + (int)fCameraPosX,
				y + (int)fCameraPosY,
				z);
			olc::vi2d tileRep = map->GetTileRepresentation(
				x + (int)fCameraPosX,
				y + (int)fCameraPosY,
				z);

			olc::Pixel ref;
			olc::Pixel toDraw;
			for (int i = 0; i < nTileSize.y; i++) {
				for (int j = 0; j < nTileSize.x; j++) {
					ref = tileSet->GetPixel(j+tileRep.x, i+tileRep.y);
					if (ref == olc::WHITE) {
						Draw(
							olc::vi2d((x*nTileSize.x) + j, (y*nTileSize.y) + i),
							tileColor
						);
					}
					else {
						Draw(
							olc::vi2d((x*nTileSize.x) + j, (y*nTileSize.y) + i),
							olc::BLACK
						);
					}
				}
			}

			// DrawPartialSprite(
			// 	olc::vi2d(x, y) * nTileSize,
			// 	tileSet,
			// 	tileRep,
			// 	nTileSize);
		}

		void DrawMap()
		{
			for (int y = 0; y < (ScreenHeight() / nTileSize.y); y++) {
				for (int x = 0; x < (ScreenWidth() / nTileSize.x); x++) {
					DrawTile(x, y, currDepth);
				}
			}
			std::string str = "Layer: ";
			str.append(std::to_string(currDepth));
			DrawString(olc::vi2d(0,0), str, olc::WHITE, 1);
		}

    protected:
		bool OnUserCreate() override
		{
			map->GenerateMap();
			nTileSize = map->GetTileSize();
			DrawMap();
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			// Press 'M' key to regenerate map
			bool redraw = false;
			if (GetKey(olc::Key::M).bReleased) {
				map->GenerateMap();
				redraw = true;
			}

			// Hold 'Z' key to move camera faster
			int mode = 1;
			if (GetKey(olc::Key::Z).bHeld) {
				mode = 4;
			}

			// Hold 'X' key to descend depth
			if (GetKey(olc::Key::X).bReleased) {
				if (currDepth != MAX_DEPTH - 1) {
					redraw = true;
					currDepth += 1;
				}
			}

			// Hold 'C' key to ascend depth
			if (GetKey(olc::Key::C).bReleased) {
				if (currDepth != 0) {
					redraw = true;
					currDepth -= 1;
				}
			}

			// Mouse Edge Map Scroll
			float fMapScrollSpeed = 100.0f * mode;

			bool left = GetKey(olc::Key::LEFT).bHeld;
			bool right = GetKey(olc::Key::RIGHT).bHeld;
			bool up = GetKey(olc::Key::UP).bHeld;
			bool down = GetKey(olc::Key::DOWN).bHeld;

			if (left)
				fCameraPosX -= fMapScrollSpeed * fElapsedTime;
			if (right)
				fCameraPosX += fMapScrollSpeed * fElapsedTime;
			if (up)
				fCameraPosY -= fMapScrollSpeed * fElapsedTime;
			if (down)
				fCameraPosY += fMapScrollSpeed * fElapsedTime;

			// Clamp map boundaries
			if (fCameraPosX < 0)
				fCameraPosX = 0;
			if (fCameraPosX >= map->GetWidth() - ScreenWidth())
				fCameraPosX = map->GetWidth() - ScreenWidth();
			if (fCameraPosY < 0)
				fCameraPosY = 0;
			if (fCameraPosY >= map->GetHeight() - ScreenHeight())
				fCameraPosY = map->GetHeight() - ScreenHeight();

			if (redraw || left || right || up || down)
				DrawMap();

			return true;
		}

	};


	int main(int argc, char const *argv[])
	{
		MarsSimulator game;

		// game.Construct(1024, 512, 1, 1); // Original size
		game.Construct(300, 200, 4, 4); // Ideal for a map from afar
		// game.Construct(256/3, 160/3, 5*3, 5*3); // Close-up

		game.Start();

		return 0;
	}
