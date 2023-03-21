#include "Instance.h"

#include <glm/ext.hpp>
#include "Scene.h"
#include "OBJMesh.h"
#include "Texture.h"
#include "SimpleCamera.h"
#include "GraphicsApp.h"
#include "Shader.h"

Instance::Instance(glm::mat4 _transform, aie::OBJMesh* _mesh, aie::ShaderProgram* _shader)
{
    m_transform = _transform;
    m_mesh = _mesh;
    m_shader = _shader;
}

void Instance::Draw(Scene* _scene)
{
    // Set the shader pipeline
    m_shader->bind();

    // Bind all relevant uniforms for our shaders
    auto pvm = _scene->GetCamera()->GetProjectionViewMatrix() * m_transform;

    m_shader->bindUniform("ProjectionViewModel", pvm);
    m_shader->bindUniform("ModelMatrix", m_transform);

    m_shader->bindUniform("CameraPosition", _scene->GetCamera()->GetPosition());
    m_shader->bindUniform("LightDirection", _scene->GetLight().direction);
    m_shader->bindUniform("LightColor", _scene->GetLight().color);
    m_shader->bindUniform("AmbientColor", _scene->GetAmbientLightColor());

    m_mesh->draw();
}
