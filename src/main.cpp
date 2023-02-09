#define OLC_PGE_APPLICATION

#if _WIN32
	#define REL_PATH_FOR_OS "assets\\tileset\\urizen.png"
#else
	#define REL_PATH_FOR_OS "assets/tileset/urizen.png"
#endif

#include <string>

#include "engine/olcPixelGameEngine.h"

#include "core/index.h"
#include "tiles/index.h"
#include "organisms/index.h"
#include "util/index.h"
#include "structures/index.h"

#define MAX_DEPTH 50

class LiveWorldEngine : public olc::PixelGameEngine
{
public:
	LiveWorldEngine() {
		sAppName = "Live World Engine";
	}

private:
	Vec2 tileSize = { 12, 12 };
	Vec2 tileOffset = { 1, 1 };
	olc::Sprite tileSet = olc::Sprite(REL_PATH_FOR_OS); // IF THE GAME IS BLACK, YOU MESSED THE PATH
	Color forePlaceholder = olc::WHITE;
	Color backPlaceholder = olc::BLACK;

	World world = World(512, 512, MAX_DEPTH);

	float cameraPosX = 0.0f;
	float cameraPosY = 0.0f;

	int currDepth = MAX_DEPTH / 2;

	void LogColor(const Color &p)
	{
		printf("R: %d, G: %d, B:%d\n", p.r, p.g, p.b);
	}

	void DrawWorld()
	{
		Clear(olc::BLACK);

		int trueX, trueY;

		bool isCurrTileEmpty;
		bool isLowerTileEmpty;
		bool isLowerTileSurface;
		for (int y = 0; y < (ScreenHeight() / tileSize.y); y++) {
			for (int x = 0; x < (ScreenWidth() / tileSize.x); x++) {
				trueX = x + (int) cameraPosX;
				trueY = y + (int) cameraPosY;

				DrawTile(x, y, currDepth);
				isCurrTileEmpty = world.GetTileTypeName(trueX, trueY, currDepth) == "empty";
				isLowerTileEmpty = world.GetTileTypeName(trueX, trueY, currDepth+1) == "empty";
				isLowerTileSurface = world.GetTileType(trueX, trueY, currDepth+1)->isSurface;
				if (isCurrTileEmpty && !isLowerTileEmpty && isLowerTileSurface) {
						DrawTile(x, y, currDepth+1);
				}
			}
		}
		std::string str = "Layer: ";
		str.append(std::to_string(currDepth));
		DrawString(Vec2(0,0), str, olc::WHITE, 1);
	}

	void DrawTile(int x, int y, int z)
	{
		Color foreColor = world.GetTileForeColor(
			x + (int)cameraPosX,
			y + (int)cameraPosY,
			z);
		Color backColor = world.GetTileBackColor(
			x + (int)cameraPosX,
			y + (int)cameraPosY,
			z);
		Vec2 spritePos = world.GetTileSprite(
			x + (int)cameraPosX,
			y + (int)cameraPosY,
			z);
		spritePos = spritePos * tileSize + (tileOffset * spritePos) + Vec2(1,1);

		Color ref;
		Vec2 screenPos;
		for (int i = 0; i < tileSize.y; i++) {
			for (int j = 0; j < tileSize.x; j++) {
				screenPos = Vec2((x*tileSize.x) + j, (y*tileSize.y) + i);
				ref = tileSet.GetPixel(j + spritePos.x, i + spritePos.y);
				if (ref == forePlaceholder)
					Draw(screenPos, foreColor);
				else
					Draw(screenPos, ref);
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
		bool redraw = false;
		if (GetKey(olc::Key::M).bReleased) {
			world.Generate();
			redraw = true;
		}

		// Press 'R' key to update entities
		if (GetKey(olc::Key::R).bReleased) {
			world.Update();
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

		if (redraw || left || right || up || down)
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
