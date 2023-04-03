#pragma once
#include <glm/gtc/constants.hpp>

#include "Mesh.h"
class Cone : public Mesh
{
public:
    Cone(int _segments, float _radius = 0.5f, float _height = 0.5f)
    {
        // Initialise the verex array
        int vertexCount = 2 + _segments;
        Vertex* vertices = new Vertex[vertexCount];

        int index = 0;
    
        // For lower center vert
        vertices[index++].position = {0, -_height, 0, 1};
        
        for (int j = 0; j < _segments; j++)
        {
            // Using unit circle, calculate the x and z pos of each vertice
            float percent = (float)j / (float)_segments;
            float radians = percent * (2 * glm::pi<float>());

            // X and Z pos of the vert using passed in radius
            float xPos = -_radius * sinf(radians);
            float zPos = -_radius * cosf(radians);

            vertices[index++].position = {xPos, -_height, zPos, 1};
        }

        // For upper center vert
        vertices[index++].position = {0, _height, 0, 1};

        // Initialise the index array
        int indexCount = 3 * (2 * _segments);
        index = 0;

        unsigned int* indices = new unsigned int[indexCount];

        // Bottom circle of tris
        for (int i = 0; i < _segments; i++)
        {
            // Initialised upside down, so they are facing outwards
            indices[index++] = i + 2;
            indices[index++] = i + 1;
            indices[index++] = 0;

            // Cleanup to prevent wrong index for tri point 1
            if (indices[index - 3] == _segments + 1)
                indices[index - 3] = indices[index - 2] - (_segments - 1);
        }

        // Top circle of tris
        for (int i = 0; i < _segments; i++)
        {
            // Initialised to be faced outwards
            indices[index++] = vertexCount - 1;
            indices[index++] = vertexCount - 1 - _segments + i;
            indices[index++] = vertexCount - 1 - _segments + i + 1;
    
            // Cleanup to prevent wrong index for tri point 3
            if (indices[index - 1] == vertexCount - 1)
                indices[index - 1] = indices[index - 2] - (_segments - 1);
        }

        this->Initialise(vertexCount, vertices, indexCount, indices);
    }
};