#include "PrimitiveScene.h"

void PrimitiveScene::Start()
{
    LoadShader();

    // Make primitives
    MakeQuad(vec3(0), vec3(10));
    MakeCube(vec3(0, 3, 0), vec3(3));
}

void PrimitiveScene::Update(float _dt)
{
    m_cubeTransform = rotate(m_cubeTransform, _dt, normalize(vec3(1, 1, 0)));
}

void PrimitiveScene::Draw()
{
    DrawMesh(m_quadMesh, m_quadTransform, vec4(0.5f, 0, 0.75f, 1));
    DrawMesh(m_cubeMesh, m_cubeTransform, vec4(1, 0, 0, 1));
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

void PrimitiveScene::MakeQuad(vec3 _position, vec3 _scale)
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
    
    m_quadTransform = translate(mat4(1), _position);
    m_quadTransform = scale(m_quadTransform, _scale);
}

void PrimitiveScene::MakeCube(vec3 _position, vec3 _scale)
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

    // Initialise the index values for the triangles
    unsigned int indices[36] = {
        2, 1, 0, 3, 1, 2,   // Bottom
        4, 5, 6, 6, 5, 7,   // Top
        6, 0, 4, 2, 0, 6,   // Left
        3, 7, 1, 1, 7, 5,   // Right
        6, 7, 2, 2, 7, 3,   // Front
        0, 5, 4, 1, 5, 0    // Back
    };

    m_cubeMesh.Initialise(8, vertices, 36, indices);
    
    m_cubeTransform = translate(mat4(1), _position);
    m_cubeTransform = scale(m_cubeTransform, _scale);
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