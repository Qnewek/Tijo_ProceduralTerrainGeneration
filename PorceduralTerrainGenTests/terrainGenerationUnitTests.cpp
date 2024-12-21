#include "pch.h"

#include "Biome.h"
#include "BiomeGenerator.h"

TEST(biomeUnitTests, biomeVerifyTest) {
	//Given
	biome::Biome b(0, "TestBiome", biome::vec2(0, 2), biome::vec2(3, 4), biome::vec2(1, 3), biome::vec2(4, 5), 0, 5);
	int T = 0, H = 3, C = 2, M = 4;

	//When
	bool result = b.verifyBiome(T, H, C, M);

	//Then
	EXPECT_TRUE(result) << "FAILED! Given temperature, humidity, continentalness and mountainousness levels does not specify tested biome.";
}

TEST(biomeGeneratorUnitTests, setBiomesTest) {
	//Given
	std::vector<biome::Biome> biomes;
	BiomeGenerator bg;

	//When
	bool result = bg.setBiomes(biomes);

	//Then
	EXPECT_FALSE(result) << "FAILED! Biomes initialization array is empty and fnc should return false";
}
TEST(biomeGeneratorUnitTests, setRangesTest) {
	//Given
	std::vector<std::vector<RangedLevel>> ranges = {
		{{-1.0f, -0.5f, 0},{-0.5f, 0.0f, 1},{0.0f, 0.5f, 2},{0.5f, 1.1f, 3}},
		{{-1.0f, -0.5f, 0},{-0.5f, 0.0f, 1},{0.0f, 0.5f, 2},{0.5f, 1.1f, 3}},
		{{-1.0f, -0.7f, 0},{-0.7f, -0.2f, 1},{ -0.2f, 0.03f, 2},{0.03f, 0.3f, 3},{0.3f, 1.1f, 4}},
		{{-1.0f, -0.78f, 0},{-0.78f, -0.37f, 1},{-0.37f, -0.2f, 2},{-0.2f, 0.05f, 3},{0.05f, 0.45f, 4},{0.45f, 0.55f, 5},{0.55f, 1.1f, 6}}
	};
	BiomeGenerator bg;
	bg.setRanges(ranges);
	int expected = -2;

	//When
	int result = bg.determineLevel(WorldParameter::Humidity, -1.5f);

	//Then
	EXPECT_EQ(expected, result) << "FAILED! Given value fit in range but should not.";
}