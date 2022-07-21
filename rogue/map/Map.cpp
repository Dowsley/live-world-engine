#include "../noise/FastNoiseLite.h"

class Map {
private:
	int nHeight;
	int nWidth;
	int nTotalSize;
	unsigned char *map;
	FastNoiseLite noise;

public:
	Map(int nWidth, int nHeight)
	{
		this->nHeight = nHeight;
		this->nWidth = nWidth;
		this->nTotalSize = nHeight * nWidth;

		map = new unsigned char[nTotalSize];
		memset(map, 0, nTotalSize * sizeof(unsigned char));
	}

	// Getters & setters
	int GetHeight() { return nHeight; }
	int GetWidth() { return nWidth; }
	unsigned char GetTile(int x, int y) { return map[y * nWidth + x]; }

	void SetHeight(int nHeight) { this->nHeight = nHeight; }
	void GetWidth(int nWidth) { this->nWidth = nWidth; }
	void SetTile(int x, int y, unsigned char val) { map[y * nWidth + x] = val; }

	// Util
	float scale(float num,float in_min, float in_max,float out_min,float out_max)
	{
		return (float) (num - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}


	// Map behaviour
	void GenerateMap()
	{
		GenerateMapOSN();
	}

	void GenerateMapRandom()
	{
		for (int y = 0; y < nHeight; y++) {
			for (int x = 0; x < nWidth; x++) {
				SetTile(x, y, rand() % 255);	
			}
		}
	}

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
		int mapped;
		for (int y = 0; y < nHeight; y++) {
			for (int x = 0; x < nWidth; x++) {
				val = noiseData[y * nWidth + x];
				// mapped = (int) (255 / 2.0f) * (val + 1.0f);
				mapped = (unsigned char) scale((float) val, -1.0f, 1.0f, 0.0f, 4.0f);
				SetTile(x, y, mapped);
			}
		}

		// Free data later
		delete[] noiseData;
	}
};






