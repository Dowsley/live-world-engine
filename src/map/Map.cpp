#include <string>

#include "../noise/FastNoiseLite.h"
#include "../tile/Tile.cpp"
#include "../util/Arithmetics.cpp"

#include "../tile/types.h"

class Map {
private:
// O--------------------------------------------O
// | TYPE DECLARATION						    |
// O--------------------------------------------O
	typedef struct LazyTile {
		unsigned char colorIndex;
		unsigned char repIndex;
		unsigned char type;
		Tile *state;
	} LazyTile;

	struct ITileType {
		olc::vi2d defaultRepresentation;
		olc::Pixel *defaultColors;
		virtual Tile *create() = 0;
	};

	template<typename T>
	struct TileType : public ITileType {
		TileType(olc::vi2d i, olc::Pixel *colors)
		{
			defaultRepresentation = i;
			defaultColors = colors;
		};
		T *create() override
		{
		return new T();
		};
	};

// O--------------------------------------------O
// | INTERNALS 								    |
// O--------------------------------------------O
	int nHeight;
	int nWidth;
	int nTotalSize;

	LazyTile *map;
	FastNoiseLite noise;

	olc::vi2d TILE_SIZE = { 8, 8 };

	static const unsigned char NUM_OF_TYPES = 2;
	ITileType *tileTypes[NUM_OF_TYPES] = {
		new TileType<RedSand>(
			olc::vi2d(7, 15) * TILE_SIZE,
			new olc::Pixel[3] {
				olc::Pixel(0xc1440eFF),
				olc::Pixel(0x9f3a0eFF),
				olc::Pixel(0x7a2c0bFF)
			}
		),
		new TileType<Rock>(
			olc::vi2d(11, 13) * TILE_SIZE,
			new olc::Pixel[3] {
				olc::Pixel(0x3c2216FF),
				olc::Pixel(0x451804FF),
				olc::Pixel(0x4a2515FF)
			}
		)
		};

	// O--------------------------------------------O
	// | TILE BEHAVIOUR 						    |
	// O--------------------------------------------O
    Tile *CreateState(unsigned char type)
    {
        return tileTypes[type]->create();
    };

    olc::Pixel GetDefaultTileColor(unsigned char type, unsigned char i)
    {
        return tileTypes[type]->defaultColors[i];
    };

    olc::vi2d GetDefaultTileRepresentation(unsigned char type)
    {
        return tileTypes[type]->defaultRepresentation;
    };

public:
	Map(int nWidth, int nHeight)
	{
		this->nHeight = nHeight;
		this->nWidth = nWidth;
		this->nTotalSize = nHeight * nWidth;

		map = (LazyTile *) malloc(sizeof(LazyTile) * nTotalSize);
		for (int i=0; i<nTotalSize; i++) {
			map[i].type = 0;
			map[i].state = nullptr;
		}
	};

// O--------------------------------------------O
// | BASIC GETTERS AND SETTERS    			    |
// O--------------------------------------------O
	olc::vi2d GetTileSize() { return TILE_SIZE; };
	int GetHeight() { return nHeight; };
	int GetWidth() { return nWidth; };
	LazyTile *GetTile(int x, int y)
	{
		return &map[y * nWidth + x];
	};
	olc::vi2d GetTileRepresentation(int x, int y)
	{
		LazyTile *t = GetTile(x, y);
		olc::vi2d p = GetDefaultTileRepresentation(t->type);
		if (t->state) {
			p = t->state->GetRepresentation();
		}
		return p;
	};
	olc::Pixel GetTileColor(int x, int y)
	{
		LazyTile *t = GetTile(x, y);
		olc::Pixel p = GetDefaultTileColor(t->type, t->colorIndex);
		if (t->state) {
			p = t->state->GetColor();
		}
		return p;
	};

	void SetHeight(int nHeight) { this->nHeight = nHeight; };
	void SetWidth(int nWidth) { this->nWidth = nWidth; };
	void SetTile(int x, int y, float val, float min, float max)
	{
		LazyTile *t = GetTile(x,y);

		t->type = (unsigned char) Arithmetics::scale(
			val,
			min,
			max,
			0.0f,
			(float) NUM_OF_TYPES
		);
		t->colorIndex = (unsigned char) rand() % 3;
		t->repIndex = (unsigned char) rand() % 3;
	};

// O--------------------------------------------O
// | MAP BEHAVIOUR			    			    |
// O--------------------------------------------O
	void GenerateMap()
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
		float *noiseData = new float[nTotalSize];
		for (int y = 0; y < nHeight; y++) {
			for (int x = 0; x < nWidth; x++) {
				noiseData[y * nWidth + x] = noise.GetNoise((float)x, (float)y);
			}
		}

		// Do something with this data...
		float val;
		for (int y = 0; y < nHeight; y++) {
			for (int x = 0; x < nWidth; x++) {
				val = noiseData[y * nWidth + x];
				SetTile(x, y, val, -1.0f, 1.0f);
			}
		}

		// Free data later
		delete[] noiseData;
	};
};
