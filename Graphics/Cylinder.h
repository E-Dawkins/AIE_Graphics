#pragma once
#include <glm/gtc/constants.hpp>

#include "Mesh.h"

class Cylinder : public Mesh
{
public:
    Cylinder(int _segments, float _radius = 0.5f, float _height = 0.5f)
    {
        // Initialise vertex array
        int vertexCount = (_segments + 1) * 2;
        Vertex* vertices = new Vertex[vertexCount];

        int index = 0;

        for(int i = 0; i < 2; i++)
        {
            float yPos = (i == 0 ? -1.f : 1.f) * _height;

            // For lower center vert
            if(i == 0) vertices[index++].position = { 0, yPos, 0, 1 };

            for(int j = 0; j < _segments; j++)
            {
                // Using unit circle, calculate the x and z pos of each vertice
                float percent = (float) j / (float) _segments;
                float radians = percent * (2 * glm::pi<float>());

                // X and Z pos of the vert using passed in radius
                float xPos = -_radius * sinf(radians);
                float zPos = -_radius * cosf(radians);

                vertices[index++].position = { xPos, yPos, zPos, 1 };
            }

            // For upper center vert
            if(i == 1) vertices[index++].position = { 0, yPos, 0, 1 };
        }

        // Initialise index array
        int triCount = _segments * 2;
        int quadCount = _segments;
        int indexCount = 3 * triCount + 6 * quadCount;
        index = 0;

        unsigned int* indices = new unsigned int[indexCount];

        // Bottom circle of tris
        for(int i = 0; i < _segments; i++)
        {
            // Initialised upside down, so they are facing outwards
            indices[index++] = i + 2;
            indices[index++] = i + 1;
            indices[index++] = 0;

            // Cleanup to prevent wrong index for tri point 1
            if(indices[index - 3] == _segments + 1)
                indices[index - 3] = indices[index - 2] - (_segments - 1);
        }

        // Middle ring of quads
        for(int i = 1; i <= _segments; i++)
        {
            // Order looks weird, but this is so the tri is facing outwards
            indices[index++] = (i % _segments) + 1;
            indices[index++] = i + 1 + _segments;
            indices[index++] = i;
            indices[index++] = i;
            indices[index++] = i + 1 + _segments;
            indices[index++] = i + _segments;

            // Cleanup to prevent wrong index of tri point 2 of each tri in quad
            if(indices[index - 2] > 2 * _segments)
                indices[index - 2] -= _segments;

            if(indices[index - 5] > 2 * _segments)
                indices[index - 5] -= _segments;
        }

        // Top circle of tris
        for(int i = 0; i < _segments; i++)
        {
            // Initialised to be faced outwards
            indices[index++] = vertexCount - 1;
            indices[index++] = vertexCount - 1 - _segments + i;
            indices[index++] = vertexCount - 1 - _segments + i + 1;

            // Cleanup to prevent wrong index for tri point 3
            if(indices[index - 1] == vertexCount - 1)
                indices[index - 1] = indices[index - 2] - (_segments - 1);
        }

        this->Initialise(vertexCount, vertices, indexCount, indices);
    }
};
