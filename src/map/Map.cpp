#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "../noise/FastNoiseLite.h"
#include "../tile/Tile.cpp"
#include "../util/Arithmetics.cpp"

#include "../tile/types.h"

typedef struct LazyTile {
	unsigned char type;
	Tile *state;
} LazyTile;

struct ITileType {
    olc::Pixel defaultRepresentation;
	virtual Tile *create() = 0;
};

template<typename T>
struct TileType : public ITileType {
    TileType(olc::Pixel dr)
	{
        defaultRepresentation = dr;
    };
	T *create() override
	{
	   return new T();
	};
};

class Map {
private:
	int nHeight;
	int nWidth;
	int nTotalSize;

	LazyTile *map;
	FastNoiseLite noise;

	static const unsigned char NUM_OF_TYPES = 2;
    ITileType *tileTypes[NUM_OF_TYPES] = {
        new TileType<RedSand>(olc::Pixel(193, 68, 14)), // Mars Red
        new TileType<Rock>(olc::Pixel(69, 24, 4))       // Mars Brown
    };

	// Individual tile behaviour
    Tile *CreateState(unsigned char type)
    {
        return tileTypes[type]->create();
    };

    olc::Pixel GetDefaultRepresentation(unsigned char type)
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

	// Getters & setters
	int GetHeight() { return nHeight; };
	int GetWidth() { return nWidth; };
	LazyTile *GetTile(int x, int y)
	{
		return &map[y * nWidth + x];
	};
	olc::Pixel GetTileRepresentation(int x, int y)
	{
		LazyTile *t = GetTile(x, y);
		olc::Pixel p = GetDefaultRepresentation(t->type);
		if (t->state) {
			p = t->state->GetRepresentation();
		}
		return p;
	};

	void SetHeight(int nHeight) { this->nHeight = nHeight; };
	void SetWidth(int nWidth) { this->nWidth = nWidth; };
	void SetTile(int x, int y, float val, float min, float max)
	{
		unsigned char mapped = (unsigned char) Arithmetics::scale(
			val,
			min,
			max,
			0.0f,
			(float) NUM_OF_TYPES
		);
		GetTile(x, y) ->type = mapped;
	};

	// Map behaviour
	void GenerateMap()
	{
		GenerateMapOSN();
	};

	void GenerateMapRandom()
	{
		for (int y = 0; y < nHeight; y++) {
			for (int x = 0; x < nWidth; x++) {
				SetTile(x, y, rand() % 255, 0.0f, 255.0f);
			}
		}
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
