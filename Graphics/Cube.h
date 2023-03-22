#pragma once
#include "Mesh.h"
class Cube : public Mesh
{
public:
    Cube()
    {
        // Define the 8 vertices for the cube
        Vertex vertices[8];

        vertices[0].position = {-0.5f, -0.5f,  0.5f, 1};
        vertices[1].position = { 0.5f, -0.5f,  0.5f, 1};
        vertices[2].position = {-0.5f, -0.5f, -0.5f, 1};
        vertices[3].position = { 0.5f, -0.5f, -0.5f, 1};
        vertices[4].position = {-0.5f,  0.5f,  0.5f, 1};
        vertices[5].position = { 0.5f,  0.5f,  0.5f, 1};
        vertices[6].position = {-0.5f,  0.5f, -0.5f, 1};
        vertices[7].position = { 0.5f,  0.5f, -0.5f, 1};

        // Initialise the index values for the 6 faces
        unsigned int indices[36] = {
            2, 1, 0, 3, 1, 2,   // Bottom
            4, 5, 6, 6, 5, 7,   // Top
            6, 0, 4, 2, 0, 6,   // Left
            3, 7, 1, 1, 7, 5,   // Right
            6, 7, 2, 2, 7, 3,   // Front
            0, 5, 4, 1, 5, 0    // Back
        };

        this->Initialise(8, vertices, 36, indices);
    }
};

