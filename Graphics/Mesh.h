#pragma once

class Mesh
{
public:
    Mesh() : m_triCount(0), m_vao(0), m_vbo(0), m_ibo(0)
    {
        
    }
    
protected:
    unsigned int m_triCount;
    unsigned int m_vao; // vertex array object
    unsigned int m_vbo; // vertex buffer object
    unsigned int m_ibo; // index buffer object
};
