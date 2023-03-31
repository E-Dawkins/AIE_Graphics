#pragma once
#include <glm/gtc/matrix_transform.hpp>

class Scene;

namespace aie
{
    class ShaderProgram;
}

using glm::mat4;
using glm::vec3;

class Instance
{
public:
    Instance() = default;
    virtual ~Instance() = default;
    
    virtual void Draw(Scene* _scene) {}

    static mat4 MakeTransform(vec3 _position, vec3 _eulerAngles, vec3 _scale)
    {
        return translate(mat4(1), _position)
        * rotate(mat4(1), glm::radians(_eulerAngles.z), vec3(0, 0, 1))
        * rotate(mat4(1), glm::radians(_eulerAngles.y), vec3(0, 1, 0))
        * rotate(mat4(1), glm::radians(_eulerAngles.x), vec3(1, 0, 0))
        * scale(mat4(1), _scale);
    }
    
protected:
    mat4 m_transform;
    aie::ShaderProgram* m_shader;
};

