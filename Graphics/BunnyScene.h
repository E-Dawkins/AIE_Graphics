#pragma once
#include "Mesh.h"
#include "OBJMesh.h"
#include "OrbitalCamera.h"
#include "Scene.h"
#include "Shader.h"

using glm::mat4;
using glm::vec3;

class BunnyScene : public Scene
{
public:
    void Start() override;
    void Update(float _dt) override;
    void Draw() override;

    void ImGuiRefresher() override;
    
    void LoadBunny();
    void LoadTexture();

    void DrawPhong();
    void DrawTextured();

protected:
    aie::Texture        m_gridTexture;
    
    aie::ShaderProgram	m_phongShader;
    aie::ShaderProgram  m_texturedShader;

    aie::OBJMesh		m_bunnyMesh;
    mat4                m_bunnyTransform;

    GraphicsApp::Light  m_light;
    vec3                m_ambientLight;

    OrbitalCamera*      m_camera;

    Mesh                m_quadMesh;
    mat4                m_quadTransform;
};