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
	std::cout << "PASSED! Map initialization successful." << std::endl;
}