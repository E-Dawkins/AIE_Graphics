#pragma once
#include "Mesh.h"
class Quad : public Mesh
{
public:
    Quad()
    {
        // Defined as 4 vertices for the 2 triangles
        Vertex vertices[4];

        vertices[0].position = {-0.5f, 0,  0.5f, 1};
        vertices[1].position = { 0.5f, 0,  0.5f, 1};
        vertices[2].position = {-0.5f, 0, -0.5f, 1};
        vertices[3].position = { 0.5f, 0, -0.5f, 1};

        // Assign the index values for the triangles
        unsigned int indices[6] = {0, 1, 2, 2, 1, 3};
    
        this->Initialise(4, vertices, 6, indices);
    }
};