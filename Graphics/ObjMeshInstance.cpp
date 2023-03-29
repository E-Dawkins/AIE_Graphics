#include "ObjMeshInstance.h"

#include "Scene.h"
#include "Shader.h"
#include "FlyCamera.h"

ObjMeshInstance::ObjMeshInstance(mat4 _transform, aie::OBJMesh& _mesh, aie::ShaderProgram& _shader)
{
    m_transform = _transform;
    m_objMesh = &_mesh;
    m_shader = &_shader;
}

ObjMeshInstance::ObjMeshInstance(vec3 _position, vec3 _eulerAngles, vec3 _scale,
    aie::OBJMesh& _mesh, aie::ShaderProgram& _shader)
{
    m_transform = MakeTransform(_position, _eulerAngles, _scale);
    m_objMesh = &_mesh;
    m_shader = &_shader;
}

void ObjMeshInstance::Draw(Scene* _scene)
{
    // Set the shader pipeline
    m_shader->bind();
    
    auto pvm = _scene->GetCamera()->GetProjectionViewMatrix() * m_transform;
    m_shader->bindUniform("ProjectionViewModel", pvm);

    // Bind all relevant uniforms for our shaders
    m_shader->bindUniform("ModelMatrix", m_transform);

    int numberOfLights = _scene->GetNumberOfLights();
    m_shader->bindUniform("numLights", numberOfLights);
    m_shader->bindUniform("PointLightPositions", numberOfLights,
        _scene->GetPointLightPositions());
    m_shader->bindUniform("PointLightColors", numberOfLights,
        _scene->GetPointLightColors());
    
    m_shader->bindUniform("CameraPosition", _scene->GetCamera()->GetPosition());
    m_shader->bindUniform("LightDirection", _scene->GetLight().direction);
    m_shader->bindUniform("LightColor", _scene->GetLight().color);
    m_shader->bindUniform("AmbientColor", _scene->GetAmbientLightColor());

    m_objMesh->draw();
}
