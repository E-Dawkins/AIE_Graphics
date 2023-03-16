#pragma once
#include <map>

#include "Mesh.h"
#include "Scene.h"
#include "Shader.h"

#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::mat4;
using glm::vec2;
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
    
    void MakeQuad();
    void MakeCube();
    void MakeCylinder();
    void MakePyramid();
    void MakeSphere();
    void MakeCone();
    void MakeGrid(int _rows, int _cols, vec2 _extents = vec2(5));

    void DrawMesh(Mesh& _mesh, mat4& _transform, vec4 _color);

    aie::ShaderProgram	m_colorShader;

    Mesh				m_quadMesh;
    mat4				m_quadTransform;

    Mesh                m_cubeMesh;
    mat4                m_cubeTransform;
    
    Mesh                m_pyramidMesh;
    mat4                m_pyramidTransform;

    Mesh                m_gridMesh;
    mat4                m_gridTransform;
};
