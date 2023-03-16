#include "PrimitiveScene.h"

void PrimitiveScene::Start()
{
    LoadShader();

    // Make primitives
    MakeQuad();
    MakeCube();
    MakePyramid();
    MakeGrid(10, 10);

    // Set transforms
    m_quadTransform = translate(mat4(1), vec3(0, 1, 0));
    
    m_cubeTransform = translate(mat4(1), vec3(0, 3, 0));

    m_pyramidTransform = translate(mat4(1), vec3(3, 2, 0));

    m_gridTransform = mat4(1);
}

void PrimitiveScene::Update(float _dt)
{
    m_cubeTransform = rotate(m_cubeTransform, _dt, vec3(1, 1, -1));
}

void PrimitiveScene::Draw()
{
    DrawMesh(m_quadMesh, m_quadTransform, vec4(0.5f, 0, 0.75f, 1));
    DrawMesh(m_cubeMesh, m_cubeTransform, vec4(1, 0, 0, 1));
    DrawMesh(m_pyramidMesh, m_pyramidTransform, vec4(0, 1, 0, 1));
    DrawMesh(m_gridMesh, m_gridTransform, vec4(0, 0, 1, 1));
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

void PrimitiveScene::MakeGrid(int _rows, int _cols, vec2 _extents)
{
    // Initialise vertex array
    float quadWidth = (_extents.x * 2.f) / _rows;
    float quadHeight = (_extents.y * 2.f) / _cols;
    int vertexCount = (_rows + 1) * (_cols + 1);
    
    std::unique_ptr<Mesh::Vertex[]> vertices{new Mesh::Vertex[vertexCount]};

    for (int i = 0; i < _rows + 1; i++)
    {
        for (int j = 0; j < _cols + 1; j++)
        {
            int index = i * (_rows + 1) + j;

            float vertXPos = -_extents.x + quadWidth * j;
            float vertZPos = -_extents.y + quadHeight * i;
            
            vertices[index].position = {vertXPos, 0, vertZPos, 1};
        }
    }

    // Initialise indices for each quad in grid
    int quadCount = _rows * _cols;
    int indexCount = 6 * quadCount;
    
    std::unique_ptr<unsigned int[]> indices{new unsigned int[indexCount]};
    
    for (int i = 0; i < quadCount; i++)
    {
        int startIndex = 6 * i;
        int offsetI = i + (i / _cols);
        
        indices[startIndex] = offsetI + 1 + _cols;
        indices[startIndex + 1] = offsetI + 1;
        indices[startIndex + 2] = offsetI;
        indices[startIndex + 3] = offsetI + 1 + _cols + 1;
        indices[startIndex + 4] = offsetI + 1;
        indices[startIndex + 5] = offsetI + 1 + _cols;
    }

    m_gridMesh.Initialise(vertexCount, vertices.get(), indexCount, indices.get());
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
