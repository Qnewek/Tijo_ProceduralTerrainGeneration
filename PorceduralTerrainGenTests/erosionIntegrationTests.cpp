#include "pch.h"

#include "erosion.h"

TEST(erosionIntegrationTests, positionTest) {
	//Given
	erosion::Erosion erosion(3, 3);
	float* heightmap = new float[9] { 0.2f, 0.3f, 0.4f, 0.3f, 0.5f, 0.4f, 0.4f, 0.5f, 0.6f };
	erosion.SetMap(heightmap);
	erosion::Droplet d(erosion::vec2(0.9f, 0.9f), 1.0f, 1.0f, 1.0f);

	//When
	erosion::vec2 g = erosion.getGradient(d.getPosition());
	d.adjustDirection(g, 0.1f);
	bool result = erosion.isOnMap(d.getPosition());

	//Then
	EXPECT_TRUE(result) << "The droplet should be on the map";
}

TEST(erosionIntegrationTests, dropletDisplacement) {
	//Given
	erosion::Erosion erosion(4, 4);
	float* heightmap = new float[16] { 0.2f, 0.3f, 0.4f, 0.5f, 0.3f, 0.5f, 0.4f, 0.6f, 0.4f, 0.5f, 0.6f, 0.7f, 0.5f, 0.6f, 0.7f, 0.8f };
	erosion.SetMap(heightmap);
	erosion::Droplet d(erosion::vec2(1.6f, 1.2f), 1.0f, 1.0f, 1.0f);
	d.adjustSediment(0.5f);
	float expected = 0.05f;
	erosion::vec2 expectedPos = erosion::vec2(1.15f, 0.3f);

	//When
	erosion::vec2 g = erosion.getGradient(d.getPosition());
	erosion::vec2 posOld = d.getPosition();
	d.adjustDirection(g, 0.1f);
	float deltaElevation = erosion.getElevationDifference(posOld, d.getPosition());
	float result = d.sedimentToGather(0.1f, deltaElevation);

	//Then
	EXPECT_NEAR(result, expected, 0.005f);
	EXPECT_NEAR(d.getPosition().x, expectedPos.x, 0.05f);
	EXPECT_NEAR(d.getPosition().y, expectedPos.y, 0.05f);
	delete[] heightmap;
}


