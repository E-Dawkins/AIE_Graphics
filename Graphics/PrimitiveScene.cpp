#include "PrimitiveScene.h"

#include "GraphicsApp.h"

void PrimitiveScene::Start()
{
    LoadQuad();
}

void PrimitiveScene::Update(float _dt)
{
    
}

void PrimitiveScene::Draw()
{
    QuadDraw();
}

void PrimitiveScene::ImGuiRefresher()
{
    
}

#pragma region Quad

void PrimitiveScene::LoadQuad()
{
    // Load the simple vert and frag shaders into the m_simpleShader variable
    m_colorShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/color.vert");
    m_colorShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/color.frag");

    if (!m_colorShader.link())
    {
        printf("Simple Shader has an Error: %s\n", m_colorShader.getLastError());
        return;
    }

    // Defined as 4 vertices for the 2 triangles
    Mesh::Vertex vertices[4];

    vertices[0].position = {-0.5f, 0,  0.5f, 1};
    vertices[1].position = { 0.5f, 0,  0.5f, 1};
    vertices[2].position = {-0.5f, 0, -0.5f, 1};
    vertices[3].position = { 0.5f, 0, -0.5f, 1};

    unsigned int indices[6] = {0, 1, 2, 2, 1, 3};

    m_quadMesh.Initialise(4, vertices, 6, indices);
	
    // This is a 10 'unit' wide quad
    m_quadTransform = scale(mat4(1), vec3(10));
}

void PrimitiveScene::QuadDraw()
{
    mat4 pvm = m_graphicsApp->pvMatrix * m_quadTransform;
    
    // Bind the shader
    m_colorShader.bind();

    // Bind the transform
    m_colorShader.bindUniform("ProjectionViewModel", pvm);
    m_colorShader.bindUniform("BaseColor", vec4(0.5f, 0, 0.75f, 1));

    // Draw the quad using the mesh's draw
    m_quadMesh.Draw();
}

#pragma endregion