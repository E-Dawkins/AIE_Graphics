#pragma once
#include <map>
#include <vector>

#include "Mesh.h"
#include "Scene.h"
#include "Shader.h"

#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SimpleCamera.h"

using glm::mat4;
using glm::vec2;
using glm::vec3;
using glm::vec4;

class PrimitiveScene
{
public:
    void Start();
    void Update(float _dt);
    void Draw();

protected:
    
    void LoadShader(char* _shaderName, aie::ShaderProgram& _shader);
    
    void MakeQuad();
    void MakeCube();
    void MakeCylinder(int _segments, float _radius = 0.5f, float _height = 0.5f);
    void MakePyramid();
    void MakeSphere(int _xSegments, int _ySegments);
    void MakeCone(int _segments, float _radius = 0.5f, float _height = 0.5f);
    void MakeGrid(int _xSegments, int _ySegments, vec2 _extents = vec2(5));

    void DrawMeshColor(Mesh& _mesh, mat4& _transform, vec4 _color);

    aie::ShaderProgram	m_colorShader;
    aie::ShaderProgram  m_phongShader;

    Mesh				m_quadMesh;
    mat4				m_quadTransform;

    Mesh                m_cubeMesh;
    mat4                m_cubeTransform;

    Mesh                m_cylinderMesh;
    mat4                m_cylinderTransform;
    
    Mesh                m_pyramidMesh;
    mat4                m_pyramidTransform;

    Mesh                m_sphereMesh;
    mat4                m_sphereTransform;

    Mesh                m_coneMesh;
    mat4                m_coneTransform;

    Mesh                m_gridMesh;
    mat4                m_gridTransform;

    int m_cameraIndex;
    std::vector<SimpleCamera*> m_allCameras;
};
