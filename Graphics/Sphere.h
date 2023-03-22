#pragma once
#include <glm/gtc/constants.hpp>

#include "Mesh.h"

class Sphere : public Mesh
{
public:
    Sphere(int _xSegments, int _ySegments)
    {
        // Initialise vertex array
        int vertexCount = 2 + (_xSegments - 1) * _ySegments;
        int index = 0;

        Vertex* vertices = new Vertex[vertexCount];

        for(int i = 0; i <= _xSegments; i++)
        {
            // Using unit circle, calculate the y-pos and radius of this ring
            float yPercent = (float) i / (float) _xSegments;
            float yRadians = yPercent * glm::pi<float>() + (-90 * (glm::pi<float>() / 180.f));

            // Y-pos and radius of this ring of the sphere
            float yPos = 0.5f * sinf(yRadians);
            float ringRadius = 0.5f * cosf(yRadians);

            for(int j = 0; j < _ySegments; j++)
            {
                // Using the unit circle, calculate the x and z pos of each vertice
                float xPercent = (float) j / (float) _ySegments;
                float xRadians = xPercent * (2 * glm::pi<float>());

                // X and Z pos of this vert on this ring of the sphere
                float xPos = -ringRadius * sinf(xRadians);
                float zPos = -ringRadius * cosf(xRadians);

                vertices[index++].position = { xPos, yPos, zPos, 1 };

                // Break this for loop at the poles, otherwise it will
                // generate _cols amount of verts with the same pos
                if(i == 0 || i == _xSegments)
                    break;
            }
        }

        // Initialise indices for each tri on sphere
        int triCount = _ySegments * 2;
        int quadCount = (_xSegments - 2) * _ySegments;
        int indexCount = 3 * triCount + 6 * quadCount;
        index = 0;

        unsigned int* indices = new unsigned int[indexCount];

        // Bottom ring of tris
        for(int i = 0; i < _ySegments; i++)
        {
            // Initialised upside down, so they are facing outwards
            indices[index++] = i + 2;
            indices[index++] = i + 1;
            indices[index++] = 0;

            // Cleanup to prevent wrong index for tri point 1
            if(indices[index - 3] == _ySegments + 1)
                indices[index - 3] = indices[index - 2] - (_ySegments - 1);
        }

        // Middle ring/s of quads
        for(int i = 1; i <= quadCount; i++)
        {
            // Current row, starting at 0
            unsigned int curRow = (i - 1) / _ySegments;

            // Index of the end of next row
            unsigned int nextRowEnd = 2 * _ySegments + curRow * _ySegments;

            // Order looks weird, but this is so the tri is facing outwards
            indices[index++] = (i % _ySegments) + curRow * _ySegments + 1;
            indices[index++] = i + 1 + _ySegments;
            indices[index++] = i;
            indices[index++] = i;
            indices[index++] = i + 1 + _ySegments;
            indices[index++] = i + _ySegments;

            // Cleanup to prevent wrong index of tri point 2 of each tri in quad
            if(indices[index - 2] > nextRowEnd)
                indices[index - 2] -= _ySegments;

            if(indices[index - 5] > nextRowEnd)
                indices[index - 5] -= _ySegments;
        }

        // Top ring of tris
        for(int i = 0; i < _ySegments; i++)
        {
            // Initialised to be faced outwards
            indices[index++] = vertexCount - 1;
            indices[index++] = vertexCount - 1 - _ySegments + i;
            indices[index++] = vertexCount - 1 - _ySegments + i + 1;

            // Cleanup to prevent wrong index for tri point 3
            if(indices[index - 1] == vertexCount - 1)
                indices[index - 1] = indices[index - 2] - (_ySegments - 1);
        }

        this->Initialise(vertexCount, vertices, indexCount, indices);
    }
};
