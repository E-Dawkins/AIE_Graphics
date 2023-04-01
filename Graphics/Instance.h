#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Scene;

namespace aie
{
    class ShaderProgram;
}

using glm::mat4;
using glm::vec3;
using glm::vec4;
using glm::quat;

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

    mat4& GetTransform() { return m_transform; }

    vec3 GetPosition()
    {
        return m_transform[3];
    }
    void SetPosition(vec3 _newPosition)
    {
        m_transform[3] = vec4(_newPosition, 1);
    }
    
    vec3 GetScale()
    {
        return {length(m_transform[0]),
                length(m_transform[1]),
                length(m_transform[2])};
    }
    void SetScale(vec3 _newScale)
    {
        vec3 oldScale = GetScale();

        m_transform[0] = (m_transform[0] / oldScale.x) * _newScale.x;
        m_transform[1] = (m_transform[1] / oldScale.y) * _newScale.y;
        m_transform[2] = (m_transform[2] / oldScale.z) * _newScale.z;
    }

    bool isActive = true;
    
protected:
    mat4 m_transform;
    aie::ShaderProgram* m_shader;
};

