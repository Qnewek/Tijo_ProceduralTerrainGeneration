#pragma once

#include <iostream>
#include <chrono>
#include <type_traits>
#include <optional>

#include "glm/glm.hpp"

#include "Noise.h"
#include "Erosion.h"
#include "TerrainGenerator.h"

namespace utilities
{
    //Different utility functions
    bool ConvertToGrayscaleImage(float* data, unsigned char* image, int width, int height);
    bool SimpleMeshIndicies(unsigned int* indices, int width, int height);
    bool GenCubeLayout(float* vertices, unsigned int* indices, float scalingFactor);
    bool parseNoiseIntoVertices(float* vertices, int width, int height, float* map, float scalingFactor, unsigned int stride, unsigned int offset);
    bool parseNoiseChunksIntoVertices(float* vertices, int width, int height, int chunkX, int chunkY, float* map, float scalingFactor, unsigned int stride, unsigned int offset);

    //Functions for dealing with 3D vectors
    bool InitializeNormals(float* vertices, unsigned int stride, unsigned int offSet, unsigned int verticesCount);
    bool CalculateNormals(float* vertices, unsigned int* indices, unsigned int stride, unsigned int offSet, unsigned int indexSize);
    bool AddVector3f(float* vertices, unsigned int index, glm::vec3 vector3f);
    bool NormalizeVector3f(float* vertices, unsigned int stride, unsigned int offSet, unsigned int verticesCount);

    //Terrain generation functions
    bool GenerateTerrainMap(noise::SimplexNoiseClass& noise, float* vertices, unsigned int* indices, unsigned int stride);
    bool CreateTerrainMesh(noise::SimplexNoiseClass& noise, float* vertices, unsigned int* indices, float scalingFactor, unsigned int stride, bool normals, bool first);
    bool PerformErosion(float* vertices, unsigned int* indices, float scalingFactor, std::optional<float*> Track, int stride, int positionsOffset, int normalsOffset, erosion::Erosion& erosion);
    void PaintBiome(float* vertices, float* map, int width, int height, unsigned int stride, unsigned int offset);
    void PaintNotByTexture(float* vertices, int width, int height, unsigned int stride, unsigned int offset);
    bool PrepareWaterSurface(TerrainGenerator terraGen, float* vertices, unsigned int* indices, float scale, float seeLevel, unsigned int stride, unsigned int offset);

    //Benchmarking function
    template <typename Func, typename... Args>
    void benchmark_void(Func func, std::string funcName, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();

        func(std::forward<Args>(args)...);

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "[LOG] Function '" << funcName << "' took: " << duration.count() << " ms" << std::endl;
    }
}