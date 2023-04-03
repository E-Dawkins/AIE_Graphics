#include "OrbitalCamera.h"

OrbitalCamera::OrbitalCamera(mat4& _target, vec3 _targetOffset, float _orbitalSpeed)
{
    m_target = _target;
    m_targetOffset = _targetOffset;
    m_orbitalSpeed = _orbitalSpeed;
    
    if (_targetOffset.y != 0)
    {
        float dist = distance(m_target[3], m_target[3] + vec4(m_targetOffset, 1));
        

        // Rotate the camera on the x-axis, to look down / up at the target
        float angle = sinf(_targetOffset.y / dist);
        m_worldTransform = rotate(m_worldTransform, angle, GetRight(m_worldTransform));
    }
}

void OrbitalCamera::Update(float _dt)
{
    m_worldTransform = rotate(m_worldTransform, m_orbitalSpeed, GetUp(m_target));

    vec3 offset =  GetRight(m_worldTransform) * m_targetOffset.x +
                    GetUp(m_worldTransform) * m_targetOffset.y +
                    GetForward(m_worldTransform) * m_targetOffset.z;
    
    SetPosition(vec3(m_target[3]) + offset);
}

void OrbitalCamera::SetTarget(mat4 _target, vec3 _targetOffset)
{
    m_target = _target;
    m_targetOffset = _targetOffset;
}