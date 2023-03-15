#include "BunnyScene.h"

#include <Application.h>
#include <imgui.h>

#include "GraphicsApp.h"

void BunnyScene::Start()
{
    m_light.color = {1, 1, 0};
    m_ambientLight = {0.5, 0.5, 0.5};
    
    LoadBunny();
}

void BunnyScene::Update(float _dt)
{
    // Rotate the light to emulate a 'day/night' cycle
    m_light.direction = normalize(vec3(cos(ImGui::GetTime() * 2.f), sin(ImGui::GetTime() * 2.f), 0));

    ImGuiRefresher();
}

void BunnyScene::Draw()
{
    // Bind the phong shader
    m_phongShader.bind();

    // Bind the camera position
    m_phongShader.bindUniform("CameraPosition",
        vec3(glm::inverse(m_graphicsApp->viewMatrix)[3]));

    mat4 pvm = m_graphicsApp->pvMatrix * m_bunnyTransform;
    
    // Bind shader uniforms
    m_phongShader.bindUniform("LightDirection", m_light.direction);
    m_phongShader.bindUniform("LightColor", m_light.color);
    m_phongShader.bindUniform("AmbientColor", m_ambientLight);
    m_phongShader.bindUniform("ProjectionViewModel", pvm);
    m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);

    // Draw using the mesh's draw
    m_bunnyMesh.draw();
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
        printf("Color Shader Error: %s\n", m_phongShader.getLastError());
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
