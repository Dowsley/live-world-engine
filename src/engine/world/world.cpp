#include "../../content/content.cpp"

#include "../util/arithmetics.cpp"
#include "../util/noise.cpp"

#include <string>

class World {
private:
	// Utils
	int height;
	int width;
	int depth;
	int totalSize;
	FastNoiseLite noise;

	// Stage
	Content content;
	Tile *map;

public:
	World(int width, int height, int depth)
	{
		this->height = height;
		this->width = width;
		this->depth = depth;
		this->totalSize = height * width * depth;

		map = (Tile *) malloc(sizeof(Tile) * totalSize);
	};

	int TransformCoords(int x, int y, int z) { return y + height * (x + width * z); };

	int GetHeight() { return height; };
	int GetWidth() { return width; };
	int GetDepth() { return depth; };
	void SetHeight(int height) { this->height = height; };
	void SetWidth(int width) { this->width = width; };
	void SetDepth(int depth) { this->depth = depth; };


	Tile *GetTile(int x, int y, int z)
	{
		return &map[TransformCoords(x,y,z)];
	};
	void SetTile(int x, int y, int z, TileType *type)
	{
		Tile *tile = GetTile(x, y, z);
		content.tiles.SetupVirginTile(tile, type);
	};

	olc::vi2d GetTileSprite(int x, int y, int z)
	{
		Tile *t = GetTile(x, y, z);
		olc::vi2d res = content.tiles.GetSprite(t);
		return res;
	};
	olc::Pixel GetTileForeColor(int x, int y, int z)
	{
		Tile *t = GetTile(x, y, z);
		olc::Pixel res = content.tiles.GetForeColor(t);
		return res;
	};
	olc::Pixel GetTileBackColor(int x, int y, int z)
	{
		Tile *t = GetTile(x, y, z);
		olc::Pixel res = content.tiles.GetBackColor(t);
		return res;
	};

	void Generate()
	{
		GenerateMapOSN();
	};
	void GenerateMapOSN()
	{
		noise.SetSeed(rand());

		// Create and configure FastNoise object
		noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		// noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);

		// noise.SetFrequency(0.01f);

		noise.SetFractalType(FastNoiseLite::FractalType_FBm);
		// noise.SetFractalType(FastNoiseLite::FractalType_Ridged);
		// noise.SetFractalType(FastNoiseLite::FractalType_PingPong);

		// Gather noise data
		float *noiseData = new float[totalSize];
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				noiseData[y * width + x] = noise.GetNoise((float)x, (float)y);
			}
		}


		// Do something with this data...
		int inverseDepth;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				inverseDepth = (int) Arithmetics::scale(
					noiseData[y * width + x],
					-1.0f,
					1.0,
					0.0f,
					(float) depth
				);

				for (int z = 0; z < depth; z++) {
					if (z >= inverseDepth) {
						SetTile(x, y, z, content.tiles.rock);
					}
					else {
						if (z > 20) {
							SetTile(x, y, z, content.tiles.redSand);
						}
						else {
							SetTile(x, y, z, content.tiles.empty);
						}
					}
				}
			}
		}

		// Free data later
		delete[] noiseData;
	};
};
