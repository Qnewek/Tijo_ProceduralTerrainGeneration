#include "pch.h"

#include "Erosion.h"

TEST(erosionUnitTests, adjustingVelocityTest) {
	//Given
	float velocity = 1.0f;
	float gravity = 1.0f;
	float elevationDiff = 0.2f;
	float expected = sqrtf((velocity * velocity) + (elevationDiff * gravity));
	erosion::Droplet droplet(erosion::vec2(0.0f,0.0f), velocity, 1.0f, 1.0f);

	//When
	droplet.adjustVelocity(elevationDiff, gravity);
	float result = droplet.getVelocity();

	//Then
	EXPECT_EQ(result, expected) << "FAILED! Result should be: " << expected << ", but was: " << result;
}

TEST(erosionUnitTests, dropSedimentTest)
{
	//Given
	float elevationDiff = 0.5f;
	float expectedDropAmount = 0.0f; //Default value for sediment, result of min(elevationDiff, sediment)
	erosion::Droplet droplet(erosion::vec2(0.0f, 0.0f), 1.0f, 1.0f, 1.0f);

	//When
	float result = droplet.dropSediment(elevationDiff);

	//Then
	EXPECT_EQ(result, expectedDropAmount) << "FAILED! Result should be: " << expectedDropAmount << ", but was: " << result;
}

TEST(erosionUnitTests, evaporationTest)
{
	//Given
	float evaporationRate = 0.01f;
	float expected = 0.99f;
	erosion::Droplet droplet(erosion::vec2(0.0f, 0.0f), 1.0f, 1.0f, 1.0f);

	//When
	droplet.evaporate(evaporationRate);
	float result = droplet.getWater();

	//Then
	EXPECT_EQ(result, expected) << "FAILED! Result should be: " << expected << ", but was: " << result;
}

TEST(erosionUnitTests, mapNullPtrInitializationTest)
{
	//Given
	float* expected = nullptr;
	erosion::Erosion e(3, 3);

	//When
	float* result = e.getMap();
	
	//Then
	EXPECT_EQ(result, expected) << "FAILED! Result should be: " << expected << ", but was: " << result;
}

TEST(erosionUnitTests, mapInitializationTest)
{
	//Given
	float* map = new float[9];
	erosion::Erosion e(3, 3);

	//When
	e.SetMap(map);
	float* result = e.getMap();

	//Then
	EXPECT_TRUE(result != nullptr) << "FAILED! Result should not be nullptr";
	delete[] map;
}

TEST(erosionUnitTests, gradientTest) {
	//Given
	erosion::vec2 pos(0.5f, 0.5f);
	erosion::vec2 expected = erosion::vec2(0.0f, 0.0f);
	erosion::Erosion e(2, 2);
	float* map = new float[4] { 0.40f, 0.70f, 0.20f, 0.40f};
	e.SetMap(map);

	expected.x = (map[1] - map[0]) * (1 - pos.y) + ((map[3] - map[2]) * pos.y);
	expected.y = (map[2] - map[0]) * (1 - pos.x) + ((map[3] - map[1]) * pos.x);

	delete[] map;

	//When
	erosion::vec2 result = e.getGradient(pos);

	//Then
	EXPECT_EQ(result.x, expected.x) << "FAILED! Result should be: " << expected.x << ", but was: " << result.x;
	EXPECT_EQ(result.y, expected.y) << "FAILED! Result should be: " << expected.y << ", but was: " << result.y;
}

TEST(erosionUnitTests, isOnMapTest) {
	//Given
	erosion::vec2 pos(3.0f, 3.0f);
	erosion::Erosion e(2, 2);

	//When
	bool result = e.isOnMap(pos);

	//Then
	EXPECT_FALSE(result) << "FAILED! Result should be: false, but was: true";
}
