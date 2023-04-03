#pragma once
#include "Mesh.h"
#include "OBJMesh.h"
#include "OrbitalCamera.h"
#include "Scene.h"
#include "Shader.h"

using glm::mat4;
using glm::vec3;

class BunnyScene
{
public:
    void Start();
    void Update(float _dt);
    void Draw();

    void ImGuiRefresher();
    

    void DrawPhong(aie::OBJMesh& _mesh, mat4& _transform, aie::ShaderProgram& _phongShader);
    void DrawTexture(aie::OBJMesh& _mesh, mat4& _transform, aie::ShaderProgram& _textureShader);
    void DrawNormalLit(aie::OBJMesh& _mesh, mat4& _transform, aie::ShaderProgram& _normalLitShader);
    
    void LoadOBJMesh(char* _filePath, aie::OBJMesh& _mesh);
    void LoadShader(char* _shaderName, aie::ShaderProgram& _shader);
    void LoadTexture(char* _filePath, aie::Texture& _texture);

protected:
    aie::OBJMesh		m_bunnyMesh;
    mat4                m_bunnyTransform;
    aie::ShaderProgram  m_bunnyShaderPhong;

    aie::OBJMesh        m_spearMesh;
    mat4                m_speartransform;
    aie::ShaderProgram  m_spearTexture;

    aie::OBJMesh        m_robotMesh;
    mat4                m_robotTransform;
    aie::ShaderProgram  m_robotShaderNormalLit;

    Light               m_light;
    vec3                m_ambientLight;

    SimpleCamera*       m_camera;

    Mesh                m_quadMesh;
    mat4                m_quadTransform;
};