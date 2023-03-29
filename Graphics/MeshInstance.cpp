#include "MeshInstance.h"

#include "Scene.h"
#include "Shader.h"
#include "FlyCamera.h"

MeshInstance::MeshInstance(glm::mat4 _transform, Mesh& _mesh,
                           aie::ShaderProgram& _shader, glm::vec4 _color)
{
    m_transform = _transform;
    m_mesh = &_mesh;
    m_shader = &_shader;
    m_color = _color;
}

MeshInstance::MeshInstance(glm::vec3 _position, glm::vec3 _eulerAngles,
    glm::vec3 _scale, Mesh& _mesh, aie::ShaderProgram& _shader, glm::vec4 _color)
{
    m_transform = MakeTransform(_position, _eulerAngles, _scale);
    m_mesh = &_mesh;
    m_shader = &_shader;
    m_color = _color;
}

void MeshInstance::Draw(Scene* _scene)
{
    m_shader->bind();
    
    auto pvm = _scene->GetCamera()->GetProjectionViewMatrix() * m_transform;
    m_shader->bindUniform("ProjectionViewModel", pvm);

    m_shader->bindUniform("BaseColor", m_color);
    
    m_mesh->Draw();
}
