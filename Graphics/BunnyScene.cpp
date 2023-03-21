#include "BunnyScene.h"

#include <Application.h>
#include <Gizmos.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GraphicsApp.h"
#include "StationaryCamera.h"

void BunnyScene::Start()
{
    m_light.color = {1, 1, 1};
    m_ambientLight = {1, 1, 1};
    
    LoadShader("normalLit", m_robotShaderNormalLit);
    LoadOBJMesh("./robot/robot.obj", m_robotMesh);
    m_robotTransform = rotate(mat4(1), glm::pi<float>(), vec3(0, 1, 0));
    m_robotTransform = scale(m_robotTransform, vec3(0.1f));
    
    m_camera = new SimpleCamera();
    m_camera->SetPosition(vec3(0, 0.75f, -3));
}

void BunnyScene::Update(float _dt)
{
    // Rotate the light to emulate a 'day/night' cycle
    m_light.direction = normalize(vec3(cos(ImGui::GetTime() * 2.f), sin(ImGui::GetTime() * 2.f), 0));

    // Update camera
    m_camera->Update(_dt);
}

void BunnyScene::Draw()
{
    DrawNormalLit(m_robotMesh, m_robotTransform, m_robotShaderNormalLit);
}

void BunnyScene::ImGuiRefresher()
{
    ImGui::Begin("LightSettings");
	
    ImGui::ColorEdit4("Global Light Color", &m_light.color[0], false);
    ImGui::ColorEdit4("Ambient Light Color", &m_ambientLight[0], false);
	
    ImGui::End();
}

void BunnyScene::DrawPhong(aie::OBJMesh& _mesh, mat4& _transform, aie::ShaderProgram& _phongShader)
{
    mat4 pvm = m_camera->GetProjectionViewMatrix() * _transform;
    
    // Bind the phong shader
    _phongShader.bind();
    
    // Bind shader uniforms
    _phongShader.bindUniform("CameraPosition", m_camera->GetPosition());
    _phongShader.bindUniform("LightDirection", m_light.direction);
    _phongShader.bindUniform("LightColor", m_light.color);
    _phongShader.bindUniform("AmbientColor", m_ambientLight);
    _phongShader.bindUniform("ProjectionViewModel", pvm);
    _phongShader.bindUniform("ModelMatrix", _transform);

    // Draw mesh
    _mesh.draw();
}

void BunnyScene::DrawTexture(aie::OBJMesh& _mesh, mat4& _transform, aie::ShaderProgram& _textureShader)
{
    mat4 pvm = m_camera->GetProjectionViewMatrix() * _transform;
    
    // Bind the textured shader
    _textureShader.bind();

    // Bind uniforms
    _textureShader.bindUniform("ProjectionViewModel", pvm);
    _textureShader.bindUniform("diffuseTexture", 0);

    // Draw mesh
    _mesh.draw();
}

void BunnyScene::DrawNormalLit(aie::OBJMesh& _mesh, mat4& _transform, aie::ShaderProgram& _normalLitShader)
{
    mat4 pvm = m_camera->GetProjectionViewMatrix() * _transform;

    // Bind the normal lit shader
    _normalLitShader.bind();
    
    // Bind uniforms
    _normalLitShader.bindUniform("CameraPosition", m_camera->GetPosition());
    _normalLitShader.bindUniform("diffuseTexture", 0);
    _normalLitShader.bindUniform("specularTexture", 1);
    _normalLitShader.bindUniform("LightDirection", m_light.direction);
    _normalLitShader.bindUniform("LightColor", m_light.color);
    _normalLitShader.bindUniform("AmbientColor", m_ambientLight);
    _normalLitShader.bindUniform("ProjectionViewModel", pvm);
    _normalLitShader.bindUniform("ModelMatrix", _transform);

    // Draw mesh
    _mesh.draw();
}

void BunnyScene::LoadOBJMesh(char* _filePath, aie::OBJMesh& _mesh)
{
    // Check if bunny mesh has loaded successfully
    if (!_mesh.load(_filePath, true, true))
    {
        printf("Mesh Error! Could not load:\n\t%s", _filePath);
        return;
    }
}

void BunnyScene::LoadShader(char* _shaderName, aie::ShaderProgram& _shader)
{
    std::string vertPath = "./shaders/";
    vertPath.append(_shaderName);
    
    std::string fragPath = vertPath;

    vertPath.append(".vert");
    fragPath.append(".frag");
    
    // Load the simple vert and frag shaders into the m_simpleShader variable
    _shader.loadShader(aie::eShaderStage::VERTEX, vertPath.c_str());
    _shader.loadShader(aie::eShaderStage::FRAGMENT, fragPath.c_str());

    if (!_shader.link())
    {
        printf("Shader Error!\n\t%s", _shader.getLastError());
        return;
    }
}

void BunnyScene::LoadTexture(char* _filePath, aie::Texture& _texture)
{
    if (!_texture.load(_filePath))
    {
        printf("Texture Error! Could not load:\n\t%s", _filePath);
        return;
    }
}