#pragma once
#include "OBJMesh.h"
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

protected:
    aie::ShaderProgram	m_phongShader;

    aie::OBJMesh		m_bunnyMesh;
    mat4                m_bunnyTransform;

    struct Light
    {
        vec3 direction;
        vec3 color;
    };

    Light m_light;
    vec3 m_ambientLight;
};
