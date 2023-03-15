#pragma once
#include <map>

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
    
    void LoadShader();
    
    void MakeQuad(vec3 _position, vec3 _scale);
    void MakeCube(vec3 _position, vec3 _scale);

    void DrawMesh(Mesh& _mesh, mat4& _transform, vec4 _color);

    aie::ShaderProgram	m_colorShader;

    Mesh				m_quadMesh;
    mat4				m_quadTransform;

    Mesh                m_cubeMesh;
    mat4                m_cubeTransform;
};
