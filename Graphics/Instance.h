#pragma once
#include <glm/glm.hpp>

#include "Mesh.h"

class SimpleCamera;
class Scene;
struct Light;

namespace aie
{
    class OBJMesh;
    class ShaderProgram;
}

class Instance
{
public:
    Instance(glm::mat4 _transform, aie::OBJMesh& _mesh,
                aie::ShaderProgram& _shader);
    Instance(glm::vec3 _position, glm::vec3 _eulerAngles, glm::vec3 _scale,
                aie::OBJMesh& _mesh, aie::ShaderProgram& _shader);
    Instance(glm::mat4 _transform, Mesh& _mesh,
                aie::ShaderProgram& _shader, glm::vec4 _color = glm::vec4(1));
    Instance(glm::vec3 _position, glm::vec3 _eulerAngles, glm::vec3 _scale,
                Mesh& _mesh, aie::ShaderProgram& _shader, glm::vec4 _color = glm::vec4(1));
    
    void Draw(Scene* _scene);

    static glm::mat4 MakeTransform(glm::vec3 _position,
        glm::vec3 _eulerAngles, glm::vec3 _scale);
    
protected:
    glm::mat4 m_transform;
    aie::OBJMesh* m_objMesh;
    aie::ShaderProgram* m_shader;
    
    Mesh* m_mesh;
    glm::vec4 m_color;
};

