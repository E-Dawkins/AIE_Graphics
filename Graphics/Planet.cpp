#include "Planet.h"

#include <Gizmos.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

Planet::Planet(vec3 _center, float _radius, vec4 _color, float _radians, Planet* _parent)
{
    m_color = _color;

    m_rotationRadians = _radians;
    m_parent = _parent;
    
    m_hasRing = false;
    
    transform = translate(mat4(1), _center);
    transform = scale(transform, vec3(_radius));
}

Planet::~Planet()
{
    delete m_parent;
}

void Planet::Update(float _dt)
{
    // Rotate the transform around local origin
    mat4 rotation = RotateAround(vec3(0), normalize(vec3(0, 1, 0)), m_rotationRadians);
    transform = rotation * transform;
}

void Planet::Draw()
{
    float averageScale = GetAverageScale(transform);
    
    // Transform relative to parent
    if (m_parent != nullptr)
        aie::Gizmos::addSphere(transform[3], averageScale, 10, 10, m_color, &m_parent->transform);

    // Transform relative to world origin
    else aie::Gizmos::addSphere(transform[3], averageScale, 10, 10, m_color);

    if (m_hasRing)
        aie::Gizmos::addRing(transform[3], averageScale * 1.25f, averageScale * 1.75f, 10, m_color);
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

void Planet::HasRing(bool _hasRing)
{
    m_hasRing = _hasRing;
}

float Planet::GetAverageScale(mat4 _transform)
{
    return (length(_transform[0]) + length(_transform[1]) + length(_transform[2])) / 3.f;
}