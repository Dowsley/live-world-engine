#define OLC_PGE_APPLICATION
#include "../engine/olcPixelGameEngine.h"
#include "map/Map.cpp"

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

		Map *map = new Map(1024, 512);

		float fCameraPosX = 0.0f;
		float fCameraPosY = 0.0f;

		void DrawTile(int x, int y)
		{
			olc::Pixel tileColor = map->GetTileColor(
				x + (int)fCameraPosX,
				y + (int)fCameraPosY);
			olc::vi2d tileRep = map->GetTileRepresentation(
				x + (int)fCameraPosX,
				y + (int)fCameraPosY);

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
					DrawTile(x,y);
				}
			}
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
			bool regen = false;
			if (GetKey(olc::Key::M).bReleased) {
				map->GenerateMap();
				regen = true;
			}

			// Mouse Edge Map Scroll
			float fMapScrollSpeed = 100.0f;

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

			if (regen || left || right || up || down)
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
