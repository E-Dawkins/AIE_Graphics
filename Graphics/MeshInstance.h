#pragma once
#include "Instance.h"

#include "Mesh.h"

class MeshInstance : public Instance
{
public:
    MeshInstance(glm::mat4 _transform, Mesh& _mesh,
                aie::ShaderProgram& _shader, glm::vec4 _color = glm::vec4(1));
    MeshInstance(glm::vec3 _position, glm::vec3 _eulerAngles, glm::vec3 _scale,
                Mesh& _mesh, aie::ShaderProgram& _shader, glm::vec4 _color = glm::vec4(1));

    ~MeshInstance() override
    {
        delete m_mesh;
    }
    
    void Draw(Scene* _scene) override;

protected:
    Mesh* m_mesh;
    glm::vec4 m_color;
};