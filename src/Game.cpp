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
		Map *map = new Map(1024, 512);

		float fCameraPosX = 0.0f;
		float fCameraPosY = 0.0f;

		void DrawMap()
		{
			olc::Pixel tileRep;
			for (int y = 0; y < ScreenHeight(); y++) {
				for (int x = 0; x < ScreenWidth(); x++) {
					tileRep = map->GetTileRepresentation(x + (int)fCameraPosX, y + (int)fCameraPosY);
					Draw(x, y, tileRep);
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

			if (GetKey(olc::Key::LEFT).bHeld)
				fCameraPosX -= fMapScrollSpeed * fElapsedTime;
			if (GetKey(olc::Key::RIGHT).bHeld)
				fCameraPosX += fMapScrollSpeed * fElapsedTime;
			if (GetKey(olc::Key::UP).bHeld)
				fCameraPosY -= fMapScrollSpeed * fElapsedTime;
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


	int main(int argc, char const *argv[])
	{
		MarsSimulator game;

		// game.Construct(1024, 512, 1, 1); // Original size
		game.Construct(256, 160, 5, 5); // Ideal for a map from afar
		// game.Construct(256/3, 160/3, 5*3, 5*3); // Close-up

		game.Start();

		return 0;
	}
