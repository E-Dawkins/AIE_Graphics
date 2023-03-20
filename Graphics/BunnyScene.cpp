#include "BunnyScene.h"

#include <Application.h>
#include <Gizmos.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GraphicsApp.h"

void BunnyScene::Start()
{
    m_light.color = {1, 1, 0};
    m_ambientLight = {0.5, 0.5, 0.5};

    LoadBunny();
    LoadTexture();

    m_camera = new OrbitalCamera(m_bunnyTransform, vec3(0, 3.5f, -20.f));
}

void BunnyScene::Update(float _dt)
{
    // Rotate the light to emulate a 'day/night' cycle
    m_light.direction = normalize(vec3(cos(ImGui::GetTime() * 2.f), sin(ImGui::GetTime() * 2.f), 0));

    ImGuiRefresher();

    // Update camera
    m_camera->Update(_dt);
}

void BunnyScene::Draw()
{
    DrawPhong();
    DrawTextured();
}

void BunnyScene::ImGuiRefresher()
{
    ImGui::Begin("LightSettings");
	
    ImGui::ColorEdit3("Global Light Color", &m_light.color[0]);
	
    ImGui::End();
}

void BunnyScene::LoadBunny()
{
    m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
    m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

    // Check if the color shader has loaded successfully
    if (!m_phongShader.link())
    {
        printf("Phong Shader Error: %s\n", m_phongShader.getLastError());
        return;
    }

    // Check if bunny mesh has loaded successfully
    if (!m_bunnyMesh.load("./stanford/Bunny.obj"))
    {
        printf("Bunny Mesh Error:\n");
        return;
    }

    m_bunnyTransform = mat4(1);
}

void BunnyScene::LoadTexture()
{
    m_texturedShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
    m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");

    // Check if the color shader has loaded successfully
    if (!m_texturedShader.link())
    {
        printf("Textured Shader Error: %s\n", m_texturedShader.getLastError());
        return;
    }

    if (!m_gridTexture.load("./textures/numbered_grid.tga"))
    {
        printf("Failed the load the grid texture correctly!\n");
        return;
    }

    m_quadMesh.InitialiseQuad();
    m_quadTransform = scale(mat4(1), vec3(10));
}

void BunnyScene::DrawPhong()
{
    // Bind the phong shader
    m_phongShader.bind();

    // Bind the camera position
    m_phongShader.bindUniform("CameraPosition", m_camera->GetPosition());

    mat4 pvm = m_camera->GetProjectionViewMatrix() * m_bunnyTransform;
    
    // Bind shader uniforms
    m_phongShader.bindUniform("LightDirection", m_light.direction);
    m_phongShader.bindUniform("LightColor", m_light.color);
    m_phongShader.bindUniform("AmbientColor", m_ambientLight);
    m_phongShader.bindUniform("ProjectionViewModel", pvm);
    m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);

    // aie::Gizmos::addAABBFilled(vec3(0), vec3(10, 0.01f, 10), vec4(1, 0, 0, 1));
    // aie::Gizmos::draw(m_camera->GetProjectionViewMatrix());

    // Draw using the mesh's draw
    m_bunnyMesh.draw();
}

void BunnyScene::DrawTextured()
{
    mat4 pvm = m_camera->GetProjectionViewMatrix() * m_quadTransform;
    
    // Bind the textured shader
    m_texturedShader.bind();

    // Bind uniforms
    m_texturedShader.bindUniform("ProjectionViewModel", pvm);
    m_texturedShader.bindUniform("diffuseTexture", 0);

    // Bind the texture to a specific location
    m_gridTexture.bind(0);

    m_quadMesh.Draw();
}
