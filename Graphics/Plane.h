#pragma once
#include "Mesh.h"
class Plane : public Mesh
{
public:
    Plane(int _xSegments, int _ySegments, glm::vec2 _extents = glm::vec2(5))
    {
        float quadWidth = (_extents.x * 2.f) / _xSegments;
        float quadHeight = (_extents.y * 2.f) / _ySegments;
        int vertexCount = (_xSegments + 1) * (_ySegments + 1);
    
        // Initialise vertex array
        Vertex* vertices = new Vertex[vertexCount];

        for (int i = 0; i <= _xSegments; i++)
        {
            for (int j = 0; j <= _ySegments; j++)
            {
                float vertXPos = -_extents.x + quadWidth * j;
                float vertZPos = -_extents.y + quadHeight * i;
            
                int index = i * (_xSegments + 1) + j;
                vertices[index].position = {vertXPos, 0, vertZPos, 1};
            }
        }

        int quadCount = _xSegments * _ySegments;
        int indexCount = 6 * quadCount;
    
        // Initialise indices for each quad in grid
        unsigned int* indices = new unsigned int[indexCount];
    
        for (int i = 0; i < quadCount; i++)
        {
            int startIndex = 6 * i;
            int offsetI = i + (i / _ySegments);
        
            indices[startIndex] = offsetI + 1 + _ySegments;
            indices[startIndex + 1] = offsetI + 1;
            indices[startIndex + 2] = offsetI;
            indices[startIndex + 3] = offsetI + 1 + _ySegments + 1;
            indices[startIndex + 4] = offsetI + 1;
            indices[startIndex + 5] = offsetI + 1 + _ySegments;
        }

        this->Initialise(vertexCount, vertices, indexCount, indices);
    }
};

