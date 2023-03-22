#include "Instance.h"

#include <glm/ext.hpp>
#include "Scene.h"
#include "OBJMesh.h"
#include "Texture.h"
#include "SimpleCamera.h"
#include "GraphicsApp.h"
#include "Shader.h"

Instance::Instance(mat4 _transform, aie::OBJMesh& _mesh, aie::ShaderProgram& _shader)
{
    m_transform = _transform;
    m_mesh = &_mesh;
    m_shader = &_shader;
}

Instance::Instance(vec3 _position, vec3 _eulerAngles, vec3 _scale,
    aie::OBJMesh& _mesh, aie::ShaderProgram& _shader)
{
    m_transform = MakeTransform(_position, _eulerAngles, _scale);
    m_mesh = &_mesh;
    m_shader = &_shader;
}

void Instance::Draw(Scene* _scene)
{
    // Set the shader pipeline
    m_shader->bind();

    // Bind all relevant uniforms for our shaders
    auto pvm = _scene->GetCamera()->GetProjectionViewMatrix() * m_transform;

    m_shader->bindUniform("ProjectionViewModel", pvm);
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

    m_mesh->draw();
}

mat4 Instance::MakeTransform(vec3 _position, vec3 _eulerAngles, vec3 _scale)
{
    return translate(mat4(1), _position)
        * rotate(mat4(1), glm::radians(_eulerAngles.z), vec3(0, 0, 1))
        * rotate(mat4(1), glm::radians(_eulerAngles.y), vec3(0, 1, 0))
        * rotate(mat4(1), glm::radians(_eulerAngles.x), vec3(1, 0, 0))
        * scale(mat4(1), _scale);
}