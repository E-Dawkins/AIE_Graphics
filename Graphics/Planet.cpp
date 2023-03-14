#include "Planet.h"

#include <Gizmos.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

Planet::Planet(vec3 _center, float _radius, vec4 _color, float _radians, Planet* _parent)
{
    m_center = _center;
    m_radius = _radius;
    m_color = _color;

    m_radians = _radians;
    m_parent = _parent;
    
    transform = translate(mat4(1), _center);
}

Planet::~Planet()
{
    delete m_parent;
}

void Planet::Update(float _dt)
{
    // Rotate the transform around its parent transform, or world origin
    mat4 rotation;
    
    if (m_parent != nullptr)
        rotation = RotateAround(m_parent->transform[3], normalize(vec3(0, 1, 0)), m_radians);

    else rotation = RotateAround(vec3(0), normalize(vec3(0, 1, 0)), m_radians);

    transform = rotation * transform;
}

void Planet::Draw()
{
    // Transform relative to parent
    if (m_parent != nullptr)
        aie::Gizmos::addSphere(transform[3], m_radius, 10, 10, m_color, &m_parent->transform);

    // Transform relative to world origin
    else aie::Gizmos::addSphere(transform[3], m_radius, 10, 10, m_color);
}

mat4 Planet::RotateAround(vec3 _point, vec3 _axis, float _radians)
{
    // World -> Local
    const mat4 localT = translate(mat4(1), -_point);
    
    // Rotation value
    const mat4 rotation = rotate(mat4(1), _radians, _axis);

    // Local -> World
    const mat4 worldT = translate(mat4(1), _point);

    // Return the local transform rotated by the radian
    // amount, then apply that rotation to the world transform
    return worldT * rotation * localT;
}
