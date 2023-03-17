#include "PrimitiveScene.h"

void PrimitiveScene::Start()
{
    LoadShader();

    // Make primitives
    MakeQuad();
    MakeCube();
    MakePyramid();
    MakeGrid(10, 10);
    MakeSphere(10, 10);
    MakeCylinder(10);

    // Set transforms
    m_quadTransform = translate(mat4(1), vec3(2, 0, 2));
    
    m_cubeTransform = translate(mat4(1), vec3(-2, 0, -2));

    m_pyramidTransform = translate(mat4(1), vec3(2, 0, -2));

    m_gridTransform = translate(mat4(1), vec3(0, -1, 0));
    m_gridTransform = scale(m_gridTransform, vec3(5));

    m_sphereTransform = translate(mat4(1), vec3(-4, 0, 0));

    m_cylinderTransform = translate(mat4(1), vec3(-2, 0, 2));
}

void PrimitiveScene::Update(float _dt)
{
    m_quadTransform = rotate(m_quadTransform, _dt, vec3(0, 1, 0));
    m_cubeTransform = rotate(m_cubeTransform, _dt, vec3(1, 1, -1));
    m_pyramidTransform = rotate(m_pyramidTransform, _dt, vec3(0, 1, 0));
    m_sphereTransform = rotate(m_sphereTransform, _dt, vec3(1, 1, -1));
    m_cylinderTransform = rotate(m_cylinderTransform, _dt, vec3(1, 1, -1));
}

void PrimitiveScene::Draw()
{
    DrawMesh(m_quadMesh, m_quadTransform, vec4(0.5f, 0, 0.75f, 1));
    DrawMesh(m_cubeMesh, m_cubeTransform, vec4(1, 0, 0, 1));
    DrawMesh(m_pyramidMesh, m_pyramidTransform, vec4(0, 1, 0, 1));
    DrawMesh(m_gridMesh, m_gridTransform, vec4(0, 0, 1, 1));
    DrawMesh(m_sphereMesh, m_sphereTransform, vec4(1, 1, 0, 1));
    DrawMesh(m_cylinderMesh, m_cylinderTransform, vec4(1, 0, 1, 1));
}

void PrimitiveScene::ImGuiRefresher()
{
    
}

void PrimitiveScene::LoadShader()
{
    // Load the simple vert and frag shaders into the m_simpleShader variable
    m_colorShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/color.vert");
    m_colorShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/color.frag");

    if (!m_colorShader.link())
    {
        printf("Simple Shader has an Error: %s\n", m_colorShader.getLastError());
        return;
    }
}

void PrimitiveScene::MakeQuad()
{
    // Defined as 4 vertices for the 2 triangles
    Mesh::Vertex vertices[4];

    vertices[0].position = {-0.5f, 0,  0.5f, 1};
    vertices[1].position = { 0.5f, 0,  0.5f, 1};
    vertices[2].position = {-0.5f, 0, -0.5f, 1};
    vertices[3].position = { 0.5f, 0, -0.5f, 1};

    // Assign the index values for the triangles
    unsigned int indices[6] = {0, 1, 2, 2, 1, 3};
    
    m_quadMesh.Initialise(4, vertices, 6, indices);
}

void PrimitiveScene::MakeCube()
{
    // Define the 8 vertices for the cube
    Mesh::Vertex vertices[8];

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

    m_cubeMesh.Initialise(8, vertices, 36, indices);
}

void PrimitiveScene::MakeCylinder(int _segments, float _radius, float _height)
{
    // Initialise vertex array
    int vertexCount = (_segments + 1) * 2;
    Mesh::Vertex* vertices = new Mesh::Vertex[vertexCount];

    int index = 0;

    for (int i = 0; i < 2; i++)
    {
        float yPos = (i == 0 ? -1.f : 1.f) * _height;

        // For lower center vert
        if (i == 0) vertices[index++].position = {0, yPos, 0, 1};
        
        for (int j = 0; j < _segments; j++)
        {
            // Using unit circle, calculate the x and z pos of each vertice
            float percent = (float)j / (float)_segments;
            float radians = percent * (2 * glm::pi<float>());

            // X and Z pos of the vert using passed in radius
            float xPos = -_radius * sinf(radians);
            float zPos = -_radius * cosf(radians);

            vertices[index++].position = {xPos, yPos, zPos, 1};
        }

        // For upper center vert
        if (i == 1) vertices[index++].position = {0, yPos, 0, 1};
    }

    // Initialise index array
    int triCount  = _segments * 2;
    int quadCount = _segments;
    int indexCount = 3 * triCount + 6 * quadCount;
    index = 0;

    unsigned int* indices = new unsigned int[indexCount];

    // Bottom ring of tris
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

    // Middle ring of quads
    for (int i = 1; i <= _segments; i++)
    {
        // Order looks weird, but this is so the tri is facing outwards
        indices[index++] = (i % _segments) + 1;
        indices[index++] = i + 1 + _segments;
        indices[index++] = i;
        indices[index++] = i;
        indices[index++] = i + 1 + _segments;
        indices[index++] = i + _segments;
    
        // Cleanup to prevent wrong index of tri point 2 of each tri in quad
        if (indices[index - 2] > 2 * _segments)
            indices[index - 2] -= _segments;
            
        if (indices[index - 5] > 2 * _segments)
            indices[index - 5] -= _segments;
    }

    // Top ring of tris
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

    m_cylinderMesh.Initialise(vertexCount, vertices, indexCount, indices);
}

void PrimitiveScene::MakePyramid()
{
    // Define the 5 vertices for the pyramid
    Mesh::Vertex vertices[5];

    vertices[0].position = {  0,   1,   0,   1};
    vertices[1].position = {-0.5f, 0,  0.5f, 1};
    vertices[2].position = { 0.5f, 0,  0.5f, 1};
    vertices[3].position = {-0.5f, 0, -0.5f, 1};
    vertices[4].position = { 0.5f, 0, -0.5f, 1};

    // Initialise the indices for the 5 faces
    unsigned int indices[18] =
    {
        3, 2, 1, 4, 2, 3,   // Bottom
        3, 1, 0,            // Left
        2, 4, 0,            // Right
        4, 3, 0,            // Front
        1, 2, 0             // Back
    };

    m_pyramidMesh.Initialise(5, vertices, 18, indices);
}

void PrimitiveScene::MakeSphere(int _xSegments, int _ySegments)
{
    // Initialise vertex array
    int vertexCount = 2 + (_xSegments - 1) * _ySegments;
    int index = 0;
    
    Mesh::Vertex* vertices = new Mesh::Vertex[vertexCount];
    
    for (int i = 0; i <= _xSegments; i++)
    {
        // Using unit circle, calculate the y-pos and radius of this ring
        float yPercent = (float)i / (float)_xSegments;
        float yRadians = yPercent * glm::pi<float>() + (-90 * (glm::pi<float>() / 180.f));

        // Y-pos and radius of this ring of the sphere
        float yPos = 0.5f * sinf(yRadians);
        float ringRadius = 0.5f * cosf(yRadians);
        
        for (int j = 0; j < _ySegments; j++)
        {
            // Using the unit circle, calculate the x and z pos of each vertice
            float xPercent = (float)j / (float)_ySegments;
            float xRadians = xPercent * (2 * glm::pi<float>());

            // X and Z pos of this vert on this ring of the sphere
            float xPos = -ringRadius * sinf(xRadians);
            float zPos = -ringRadius * cosf(xRadians);
            
            vertices[index++].position = {xPos, yPos, zPos, 1};
            
            // Break this for loop at the poles, otherwise it will
            // generate _cols amount of verts with the same pos
            if (i == 0 || i == _xSegments)
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
    for (int i = 0; i < _ySegments; i++)
    {
        // Initialised upside down, so they are facing outwards
        indices[index++] = i + 2;
        indices[index++] = i + 1;
        indices[index++] = 0;

        // Cleanup to prevent wrong index for tri point 1
        if (indices[index - 3] == _ySegments + 1)
            indices[index - 3] = indices[index - 2] - (_ySegments - 1);
    }

    // Middle ring/s of quads
    for (int i = 1; i <= quadCount; i++)
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
        if (indices[index - 2] > nextRowEnd)
            indices[index - 2] -= _ySegments;
            
        if (indices[index - 5] > nextRowEnd)
            indices[index - 5] -= _ySegments;
    }

    // Top ring of tris
    for (int i = 0; i < _ySegments; i++)
    {
        // Initialised to be faced outwards
        indices[index++] = vertexCount - 1;
        indices[index++] = vertexCount - 1 - _ySegments + i;
        indices[index++] = vertexCount - 1 - _ySegments + i + 1;

        // Cleanup to prevent wrong index for tri point 3
        if (indices[index - 1] == vertexCount - 1)
            indices[index - 1] = indices[index - 2] - (_ySegments - 1);
    }

    m_sphereMesh.Initialise(vertexCount, vertices, indexCount, indices);
}

void PrimitiveScene::MakeGrid(int _xSegments, int _ySegments, vec2 _extents)
{
    float quadWidth = (_extents.x * 2.f) / _xSegments;
    float quadHeight = (_extents.y * 2.f) / _ySegments;
    int vertexCount = (_xSegments + 1) * (_ySegments + 1);
    
    // Initialise vertex array
    Mesh::Vertex* vertices = new Mesh::Vertex[vertexCount];

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

    m_gridMesh.Initialise(vertexCount, vertices, indexCount, indices);
}

void PrimitiveScene::DrawMesh(Mesh& _mesh, mat4& _transform, vec4 _color)
{
    mat4 pvm = m_graphicsApp->pvMatrix * _transform;
    
    // Bind the shader
    m_colorShader.bind();

    // Bind the transform
    m_colorShader.bindUniform("ProjectionViewModel", pvm);
    m_colorShader.bindUniform("BaseColor", _color);

    // Draw the quad using the mesh's draw
    _mesh.Draw();
}
