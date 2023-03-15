#pragma once
#include "Mesh.h"
#include "Scene.h"
#include "Shader.h"

#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec4;

class PrimitiveScene : public Scene
{
public:
    void Start() override;
    void Update(float _dt) override;
    void Draw() override;
    void ImGuiRefresher() override;

protected:
    void LoadQuad();
    void QuadDraw();

    aie::ShaderProgram	m_colorShader;

    Mesh				m_quadMesh;
    mat4				m_quadTransform;
};
