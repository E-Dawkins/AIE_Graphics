#pragma once
#include "Mesh.h"
class Pyramid : public Mesh
{
public:
    Pyramid()
    {
        // Define the 5 vertices for the pyramid
        Vertex vertices[5];

        vertices[0].position = {  0,    0.5f,   0,   1};
        vertices[1].position = {-0.5f, -0.5f,  0.5f, 1};
        vertices[2].position = { 0.5f, -0.5f,  0.5f, 1};
        vertices[3].position = {-0.5f, -0.5f, -0.5f, 1};
        vertices[4].position = { 0.5f, -0.5f, -0.5f, 1};

        // Initialise the indices for the 5 faces
        unsigned int indices[18] =
        {
            3, 2, 1, 4, 2, 3,   // Bottom
            3, 1, 0,            // Left
            2, 4, 0,            // Right
            4, 3, 0,            // Front
            1, 2, 0             // Back
        };

        this->Initialise(5, vertices, 18, indices);
    }
};

