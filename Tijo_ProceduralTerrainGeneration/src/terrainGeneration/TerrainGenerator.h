#pragma once

#include <vector>

#include "Noise.h"

#include "Splines/spline.h"

struct vec2
{
	int x, y;
};

class TerrainGenerator
{
public:
	TerrainGenerator();
	~TerrainGenerator();

	bool initializeMap();

	bool setSize(int width, int height);
	void setSeed(int seed);
	bool setSeeLevel(float seeLevel);
	bool setChunkResolution(int resolution);
	void setContinentalnessNoiseConfig(noise::NoiseConfigParameters config);
	void setMountainousNoiseConfig(noise::NoiseConfigParameters config);
	void setPVNoiseConfig(noise::NoiseConfigParameters config);
	bool setSplines(std::vector<std::vector<double>> splines);

	float getSeeLevel() const { return seeLevel;};
	float* getHeightMap();
	int getWidth() const { return width * chunkResolution; };
	int getHeight() const { return height * chunkResolution; };
	noise::NoiseConfigParameters& getContinentalnessNoiseConfig();
	noise::NoiseConfigParameters& getMountainousNoiseConfig();
	noise::NoiseConfigParameters& getPVNoiseConfig();

	bool generateHeightMap();
	bool performTerrainGeneration();

private:
	float* heightMap;
	int seed;
	int width, height, water;
	int chunkResolution;
	float seeLevel;

	noise::SimplexNoiseClass continentalnessNoise;
	noise::SimplexNoiseClass mountainousNoise;
	noise::SimplexNoiseClass PVNoise;

	tk::spline continentalnessSpline;
	tk::spline mountainousSpline;
	tk::spline PVSpline;
};