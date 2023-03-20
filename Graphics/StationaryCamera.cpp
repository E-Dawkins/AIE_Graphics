#include "StationaryCamera.h"

#include <glm/gtc/matrix_transform.hpp>

StationaryCamera::StationaryCamera(vec3 _position, vec3 _rotation)
{
    m_worldTransform[3] = vec4(_position, 1);
    
    SetRotation(_rotation);
}

void StationaryCamera::SetRotation(vec3 _rotation)
{
    mat4 newMatrix = translate(mat4(1), GetPosition());
    
    newMatrix = rotate(newMatrix, _rotation.x, vec3(1, 0, 0));
    newMatrix = rotate(newMatrix, _rotation.y, vec3(0, 1, 0));
    newMatrix = rotate(newMatrix, _rotation.z, vec3(0, 0, 1));

    newMatrix = scale(newMatrix, GetScale());

    m_worldTransform = newMatrix;
}

mat4 StationaryCamera::GetRotation()
{
    vec3 scale = GetScale();

    mat4 rotation =
    {
        m_worldTransform[0] / scale.x,
        m_worldTransform[1] / scale.y,
        m_worldTransform[2] / scale.z,
        m_worldTransform[3]
    };

    return rotation;
}
