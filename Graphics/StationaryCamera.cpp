#include "StationaryCamera.h"

StationaryCamera::StationaryCamera(vec3 _position, vec3 _rotation)
{
    m_worldTransform[3] = vec4(_position, 1);
    SetRotation(_rotation);
}