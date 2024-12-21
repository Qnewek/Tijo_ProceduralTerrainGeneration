#include "pch.h"

#include "TerrainGenerator.h"

TEST(terrainGeneratorIntegrationTests, initializeMapTest) {
	//Given
	TerrainGenerator tg;
	int width = 10, height = 10, chunkResolution = 10;
	tg.setSize(width, height);
	tg.setChunkResolution(chunkResolution);

	//When
	bool result = tg.initializeMap();

	//Then
	EXPECT_TRUE(result) << "FAILED! Map initialization failed.";
}

TEST(terrainGeneratorIntegrationTests, heightMapGenerationTest) {
	//Given
	TerrainGenerator terrainGen;
	terrainGen.setSize(10, 10);
	terrainGen.setChunkResolution(5);
	terrainGen.setSeed(742);

	terrainGen.getContinentalnessNoiseConfig().constrast = 1.5f;
	terrainGen.getContinentalnessNoiseConfig().octaves = 7;
	terrainGen.getContinentalnessNoiseConfig().scale = 0.05f;

	terrainGen.getMountainousNoiseConfig().constrast = 1.5f;
	terrainGen.getMountainousNoiseConfig().scale = 0.05f;

	terrainGen.getPVNoiseConfig().constrast = 1.5f;
	terrainGen.getPVNoiseConfig().ridgeGain = 3.0f;
	terrainGen.getPVNoiseConfig().scale = 0.05f;

	terrainGen.initializeMap();
	terrainGen.setSplines({ {-1.0, -0.7, -0.2, 0.03, 0.3, 1.0}, {0.0, 40.0 ,64.0, 66.0, 68.0, 70.0},	//Continentalness {X,Y}
							{-1.0, -0.78, -0.37, -0.2, 0.05, 0.45, 0.55, 1.0}, {0.0, 5.0, 10.0, 20.0, 30.0, 80.0, 100.0, 170.0},	//Mountainousness {X,Y}
							{-1.0, -0.85, -0.6, 0.2, 0.7, 1.0}, {1.0, 0.7, 0.4, 0.2, 0.05, 0} }); //PV {X,Y}
	int expected = 457877;

	//When
	bool result = terrainGen.generateHeightMap();
	int resultHeight = static_cast<int>(terrainGen.getHeightAt(0, 0) * 10000); // rounded and casted to int due to float precision

	//Then
	EXPECT_TRUE(result) << "FAILED! Height map generation failed.";
	EXPECT_EQ(resultHeight, expected);
}

TEST(terrainGeneratorIntegrationTests, biomeMapGenerationTest) {
	//Given
	TerrainGenerator terrainGen;
	terrainGen.setSize(10, 10);
	terrainGen.setChunkResolution(5);
	terrainGen.setSeed(742);

	terrainGen.getContinentalnessNoiseConfig().constrast = 1.5f;
	terrainGen.getContinentalnessNoiseConfig().octaves = 7;
	terrainGen.getContinentalnessNoiseConfig().scale = 0.05f;

	terrainGen.getMountainousNoiseConfig().constrast = 1.5f;
	terrainGen.getMountainousNoiseConfig().scale = 0.05f;

	terrainGen.getPVNoiseConfig().constrast = 1.5f;
	terrainGen.getPVNoiseConfig().ridgeGain = 3.0f;
	terrainGen.getPVNoiseConfig().scale = 0.05f;

	terrainGen.initializeMap();
	terrainGen.setSplines({ {-1.0, -0.7, -0.2, 0.03, 0.3, 1.0}, {0.0, 40.0 ,64.0, 66.0, 68.0, 70.0},	//Continentalness {X,Y}
							{-1.0, -0.78, -0.37, -0.2, 0.05, 0.45, 0.55, 1.0}, {0.0, 5.0, 10.0, 20.0, 30.0, 80.0, 100.0, 170.0},	//Mountainousness {X,Y}
							{-1.0, -0.85, -0.6, 0.2, 0.7, 1.0}, {1.0, 0.7, 0.4, 0.2, 0.05, 0} }); //PV {X,Y}
	
	std::vector<biome::Biome> biomes = {
		biome::Biome(0, "Grassplains",	{1, 2}, {1, 4}, {3, 5}, {0, 3}, 3, 5 * 5 * 0.2f),
		biome::Biome(1, "Desert",		{2, 4}, {0, 1}, {3, 5}, {0, 4}, 2, 5 * 5 * 0.01f),
		biome::Biome(2, "Snow",			{0, 1}, {0, 4}, {3, 5}, {0, 4}, 7, 5 * 5 * 0.03f),
		biome::Biome(3, "Sand",			{0, 4}, {0, 4}, {2, 3}, {0, 7}, 8, 5 * 5 * 0.01f),
		biome::Biome(4, "Mountain",		{0, 4}, {0, 4}, {4, 5}, {4, 7}, 0, 5 * 5 * 0.02f),
		biome::Biome(5, "Ocean",		{0, 4}, {0, 4}, {0, 2}, {0, 7}, 5, 5 * 5 * 0.0f)
	};

	std::vector<std::vector<RangedLevel>> ranges = {
		{{-1.0f, -0.5f, 0},{-0.5f, 0.0f, 1},{0.0f, 0.5f, 2},{0.5f, 1.1f, 3}},
		{{-1.0f, -0.5f, 0},{-0.5f, 0.0f, 1},{0.0f, 0.5f, 2},{0.5f, 1.1f, 3}},
		{{-1.0f, -0.7f, 0},{-0.7f, -0.2f, 1},{ -0.2f, 0.03f, 2},{0.03f, 0.3f, 3},{0.3f, 1.1f, 4}},
		{{-1.0f, -0.78f, 0},{-0.78f, -0.37f, 1},{-0.37f, -0.2f, 2},{-0.2f, 0.05f, 3},{0.05f, 0.45f, 4},{0.45f, 0.55f, 5},{0.55f, 1.1f, 6}}
	};

	terrainGen.setBiomes(biomes);
	terrainGen.setRanges(ranges);

	int expected = 5;


	//When
	bool result = terrainGen.generateBiomes();
	int resultBiome = terrainGen.getBiomeAt(3, 3);

	//Then
	EXPECT_TRUE(result) << "FAILED! Biome map generation failed.";
	EXPECT_EQ(resultBiome, expected);
}

TEST(terrainGeneratorIntegrationTests, vegetationGeneratorTest) {
	//Given
	TerrainGenerator terrainGen;
	terrainGen.setSize(10, 10);
	terrainGen.setChunkResolution(5);
	terrainGen.setSeed(742);

	terrainGen.getContinentalnessNoiseConfig().constrast = 1.5f;
	terrainGen.getContinentalnessNoiseConfig().octaves = 7;
	terrainGen.getContinentalnessNoiseConfig().scale = 0.05f;

	terrainGen.getMountainousNoiseConfig().constrast = 1.5f;
	terrainGen.getMountainousNoiseConfig().scale = 0.05f;

	terrainGen.getPVNoiseConfig().constrast = 1.5f;
	terrainGen.getPVNoiseConfig().ridgeGain = 3.0f;
	terrainGen.getPVNoiseConfig().scale = 0.05f;

	terrainGen.initializeMap();
	terrainGen.setSplines({ {-1.0, -0.7, -0.2, 0.03, 0.3, 1.0}, {0.0, 40.0 ,64.0, 66.0, 68.0, 70.0},	//Continentalness {X,Y}
							{-1.0, -0.78, -0.37, -0.2, 0.05, 0.45, 0.55, 1.0}, {0.0, 5.0, 10.0, 20.0, 30.0, 80.0, 100.0, 170.0},	//Mountainousness {X,Y}
							{-1.0, -0.85, -0.6, 0.2, 0.7, 1.0}, {1.0, 0.7, 0.4, 0.2, 0.05, 0} }); //PV {X,Y}

	std::vector<biome::Biome> biomes = {
		biome::Biome(0, "Grassplains",	{1, 2}, {1, 4}, {3, 5}, {0, 3}, 3, 5 * 5 * 0.2f),
		biome::Biome(1, "Desert",		{2, 4}, {0, 1}, {3, 5}, {0, 4}, 2, 5 * 5 * 0.01f),
		biome::Biome(2, "Snow",			{0, 1}, {0, 4}, {3, 5}, {0, 4}, 7, 5 * 5 * 0.03f),
		biome::Biome(3, "Sand",			{0, 4}, {0, 4}, {2, 3}, {0, 7}, 8, 5 * 5 * 0.01f),
		biome::Biome(4, "Mountain",		{0, 4}, {0, 4}, {4, 5}, {4, 7}, 0, 5 * 5 * 0.02f),
		biome::Biome(5, "Ocean",		{0, 4}, {0, 4}, {0, 2}, {0, 7}, 5, 5 * 5 * 0.0f)
	};

	std::vector<std::vector<RangedLevel>> ranges = {
		{{-1.0f, -0.5f, 0},{-0.5f, 0.0f, 1},{0.0f, 0.5f, 2},{0.5f, 1.1f, 3}},
		{{-1.0f, -0.5f, 0},{-0.5f, 0.0f, 1},{0.0f, 0.5f, 2},{0.5f, 1.1f, 3}},
		{{-1.0f, -0.7f, 0},{-0.7f, -0.2f, 1},{ -0.2f, 0.03f, 2},{0.03f, 0.3f, 3},{0.3f, 1.1f, 4}},
		{{-1.0f, -0.78f, 0},{-0.78f, -0.37f, 1},{-0.37f, -0.2f, 2},{-0.2f, 0.05f, 3},{0.05f, 0.45f, 4},{0.45f, 0.55f, 5},{0.55f, 1.1f, 6}}
	};

	terrainGen.setBiomes(biomes);
	terrainGen.setRanges(ranges);

	std::pair<int, int> expected = { 11, 3 };
	int expectedCount = 137;

	//when
	bool result = terrainGen.performTerrainGeneration();
	auto vegetationPoints = terrainGen.getVegetationPoints();
	std::pair<int, int> resultVegetation = vegetationPoints[2][4];
	int resCount = terrainGen.getTreeCount();

	//Then
	EXPECT_TRUE(result) << "FAILED! Vegetation generation failed.";
	EXPECT_EQ(resultVegetation, expected);
	EXPECT_EQ(resCount, expectedCount);
}

TEST(terrainGeneratorIntegrationTests, nosieGenerationTest) {
	//Given
	noise::SimplexNoiseClass n;
	n.setSeed(742);
	n.setMapSize(10, 10);
	n.setChunkSize(5,5);
	n.initMap();
	float expected = 0.16376f;

	//When
	n.generateFractalNoiseByChunks();
	float result = n.getVal(7, 7);

	//Then
	EXPECT_NEAR(result, expected, 0.000005f) << "FAILED! Noise generation failed.";
}

TEST(terrainGeneratorIntegrationTests, nonValidMapGenTest) {
	//Given
	TerrainGenerator tg;
	int width = 10, height = 10, chunkResolution = 10;
	tg.setSize(width, height);
	tg.setChunkResolution(chunkResolution);

	//When
	bool result = tg.generateHeightMap();

	//Then
	EXPECT_FALSE(result) << "FAILED! Map generation should fail.";
}

TEST(terrainGeneratorIntegrationTests, nonValidBiomeGenTest) {
	//Given
	TerrainGenerator tg;
	int width = 10, height = 0, chunkResolution = 10;
	tg.setSize(width, height);
	tg.setChunkResolution(chunkResolution);

	//When
	bool result = tg.generateBiomes();

	//Then
	EXPECT_FALSE(result) << "FAILED! Biome generation should fail.";
}

TEST(terrainGeneratorIntegrationTests, nonValidAverageBiomeCalculationTest) {
	//Given
	TerrainGenerator terrainGen;
	terrainGen.setSize(10, 10);
	terrainGen.setChunkResolution(5);
	terrainGen.setSeed(742);

	terrainGen.getContinentalnessNoiseConfig().constrast = 1.5f;
	terrainGen.getContinentalnessNoiseConfig().octaves = 7;
	terrainGen.getContinentalnessNoiseConfig().scale = 0.05f;

	terrainGen.getMountainousNoiseConfig().constrast = 1.5f;
	terrainGen.getMountainousNoiseConfig().scale = 0.05f;

	terrainGen.getPVNoiseConfig().constrast = 1.5f;
	terrainGen.getPVNoiseConfig().ridgeGain = 3.0f;
	terrainGen.getPVNoiseConfig().scale = 0.05f;

	terrainGen.setSplines({ {-1.0, -0.7, -0.2, 0.03, 0.3, 1.0}, {0.0, 40.0 ,64.0, 66.0, 68.0, 70.0},	//Continentalness {X,Y}
							{-1.0, -0.78, -0.37, -0.2, 0.05, 0.45, 0.55, 1.0}, {0.0, 5.0, 10.0, 20.0, 30.0, 80.0, 100.0, 170.0},	//Mountainousness {X,Y}
							{-1.0, -0.85, -0.6, 0.2, 0.7, 1.0}, {1.0, 0.7, 0.4, 0.2, 0.05, 0} }); //PV {X,Y}

	std::vector<biome::Biome> biomes = {
		biome::Biome(0, "Grassplains",	{1, 2}, {1, 4}, {3, 5}, {0, 3}, 3, 5 * 5 * 0.2f),
		biome::Biome(1, "Desert",		{2, 4}, {0, 1}, {3, 5}, {0, 4}, 2, 5 * 5 * 0.01f),
		biome::Biome(2, "Snow",			{0, 1}, {0, 4}, {3, 5}, {0, 4}, 7, 5 * 5 * 0.03f),
		biome::Biome(3, "Sand",			{0, 4}, {0, 4}, {2, 3}, {0, 7}, 8, 5 * 5 * 0.01f),
		biome::Biome(4, "Mountain",		{0, 4}, {0, 4}, {4, 5}, {4, 7}, 0, 5 * 5 * 0.02f),
		biome::Biome(5, "Ocean",		{0, 4}, {0, 4}, {0, 2}, {0, 7}, 5, 5 * 5 * 0.0f)
	};

	std::vector<std::vector<RangedLevel>> ranges = {
		{{-1.0f, -0.5f, 0},{-0.5f, 0.0f, 1},{0.0f, 0.5f, 2},{0.5f, 1.1f, 3}},
		{{-1.0f, -0.5f, 0},{-0.5f, 0.0f, 1},{0.0f, 0.5f, 2},{0.5f, 1.1f, 3}},
		{{-1.0f, -0.7f, 0},{-0.7f, -0.2f, 1},{ -0.2f, 0.03f, 2},{0.03f, 0.3f, 3},{0.3f, 1.1f, 4}},
		{{-1.0f, -0.78f, 0},{-0.78f, -0.37f, 1},{-0.37f, -0.2f, 2},{-0.2f, 0.05f, 3},{0.05f, 0.45f, 4},{0.45f, 0.55f, 5},{0.55f, 1.1f, 6}}
	};

	//When
	terrainGen.initializeMap();
	terrainGen.setBiomes(biomes);
	terrainGen.setRanges(ranges);
	terrainGen.generateBiomes();
	terrainGen.deinitalizeBiomeMap();
	bool result = terrainGen.generateBiomeMapPerChunk();

	//Then
	EXPECT_FALSE(result);
}

