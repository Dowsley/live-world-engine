#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <math.h>

class Map {
private:
	int nHeight;
	int nWidth;
	int nTotalSize;
	unsigned char *map;

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

	// Map behaviour
	void GenerateMap()
	{
		for (int y = 0; y < nHeight; y++) {
			for (int x = 0; x < nWidth; x++) {
				SetTile(x, y, rand() % 255);	
			}
		}
	}
};






