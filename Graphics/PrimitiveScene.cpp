#include "PrimitiveScene.h"

#include <imgui.h>
#include <Input.h>
#include <string>

#include "StationaryCamera.h"

void PrimitiveScene::Start()
{
    m_allCameras.push_back(new StationaryCamera(vec3(0, 0, -20), vec3(0, 0, 0)));
    m_allCameras.push_back(new StationaryCamera(vec3(-20, 0, 0), vec3(0, -glm::pi<float>() * 0.5f, 0)));
    m_allCameras.push_back(new StationaryCamera(vec3(0, 0, 20), vec3(0, glm::pi<float>(), 0)));
    m_allCameras.push_back(new StationaryCamera(vec3(20, 0, 0), vec3(0, glm::pi<float>() * 0.5f, 0)));
    m_allCameras.push_back(new StationaryCamera(vec3(0, -20, 0), vec3(glm::pi<float>() * 0.5f, 0, 0)));
    m_allCameras.push_back(new StationaryCamera(vec3(0, 20, 0), vec3(-glm::pi<float>() * 0.5f, 0, 0)));
	
    m_cameraIndex = 0;
    
    LoadShader("color", m_colorShader);

    // Set transforms
    m_quadTransform = translate(mat4(1), vec3(2, 0, 2));
    
    m_cubeTransform = translate(mat4(1), vec3(-2, 0, -2));

    m_pyramidTransform = translate(mat4(1), vec3(2, 0, -2));

    m_gridTransform = translate(mat4(1), vec3(0, -1, 0));
    m_gridTransform = scale(m_gridTransform, vec3(5));

    m_sphereTransform = translate(mat4(1), vec3(-4, 0, 0));

    m_cylinderTransform = translate(mat4(1), vec3(-2, 0, 2));

    m_coneTransform = translate(mat4(1), vec3(4, 0, 0));
}

void PrimitiveScene::Update(float _dt)
{
    m_quadTransform = rotate(m_quadTransform, _dt, vec3(1, 1, -1));
    m_cubeTransform = rotate(m_cubeTransform, _dt, vec3(1, 1, -1));
    m_pyramidTransform = rotate(m_pyramidTransform, _dt, vec3(1, 1, -1));
    m_sphereTransform = rotate(m_sphereTransform, _dt, vec3(1, 1, -1));
    m_cylinderTransform = rotate(m_cylinderTransform, _dt, vec3(1, 1, -1));
    m_coneTransform = rotate(m_coneTransform, _dt, vec3(1, 1, -1));

    aie::Input* input = aie::Input::getInstance();
    
    // Switch cameras
    if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
    {
        m_cameraIndex = (m_cameraIndex + 1) % m_allCameras.size();
    }

    m_allCameras[m_cameraIndex]->Update(_dt);
}

void PrimitiveScene::Draw()
{
    DrawMeshColor(m_quadMesh, m_quadTransform, vec4(0.5f, 0, 0.75f, 1));
    DrawMeshColor(m_cubeMesh, m_cubeTransform, vec4(1, 0, 0, 1));
    DrawMeshColor(m_pyramidMesh, m_pyramidTransform, vec4(0, 1, 0, 1));
    DrawMeshColor(m_gridMesh, m_gridTransform, vec4(0, 0, 1, 1));
    DrawMeshColor(m_sphereMesh, m_sphereTransform, vec4(1, 1, 0, 1));
    DrawMeshColor(m_cylinderMesh, m_cylinderTransform, vec4(1, 0, 1, 1));
    DrawMeshColor(m_coneMesh, m_coneTransform, vec4(0, 1, 1, 1));
}

void PrimitiveScene::LoadShader(char* _shaderName, aie::ShaderProgram& _shader)
{
    std::string vertPath = "./shaders/";
    vertPath.append(_shaderName);
    
    std::string fragPath = vertPath;

    vertPath.append(".vert");
    fragPath.append(".frag");

    printf(vertPath.c_str());
    printf(fragPath.c_str());
    
    // Load the simple vert and frag shaders into the m_simpleShader variable
    _shader.loadShader(aie::eShaderStage::VERTEX, vertPath.c_str());
    _shader.loadShader(aie::eShaderStage::FRAGMENT, fragPath.c_str());

    if (!_shader.link())
    {
        printf("Simple Shader has an Error: %s\n", _shader.getLastError());
        return;
    }
}

void PrimitiveScene::DrawMeshColor(Mesh& _mesh, mat4& _transform, vec4 _color)
{
    mat4 pvm = m_allCameras[m_cameraIndex]->GetProjectionViewMatrix() * _transform;
    
    // Bind the shader
    m_colorShader.bind();

    // Bind the transform
    m_colorShader.bindUniform("ProjectionViewModel", pvm);
    m_colorShader.bindUniform("BaseColor", _color);

    // Draw the quad using the mesh's draw
    _mesh.Draw();
}