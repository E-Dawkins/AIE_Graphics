#include "Planet.h"

#include <Gizmos.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

Planet::Planet(char* _name, vec3 _center, float _radius, vec4 _color, float _radians, Planet* _parent)
{
    name = _name;
    
    color = _color;

    m_rotationRadians = _radians;
    m_parent = _parent;
    
    m_hasRing = false;
    
    transform = translate(mat4(1), _center);
    transform = scale(transform, vec3(_radius));

    isVisible = true;

    m_rotationMultiplier = 1.f;
}

Planet::~Planet()
{
    delete m_parent;
}

void Planet::Update(float _dt)
{
    if (m_rotationRadians != 0.f)
    {
        // Rotate the transform around local origin
        mat4 rotation = RotateAround(vec3(0), normalize(vec3(0, 1, 0)), m_rotationRadians * m_rotationMultiplier);
        transform = rotation * transform;
    }

    for (auto moon : m_moons)
        moon->Update(_dt);
}

void Planet::Draw()
{
    if (!isVisible)
        return;
    
    float averageScale = GetAverageScale(transform);
    
    // Transform relative to parent
    if (m_parent != nullptr)
    {
        aie::Gizmos::addSphere(transform[3], averageScale, 10, 10, color, &m_parent->transform);
        
        if (m_hasRing)
            aie::Gizmos::addRing(transform[3], 1.25f * averageScale, 1.75f * averageScale, 10, color, &m_parent->transform);
    }

    // Transform relative to world origin
    else
    {
        aie::Gizmos::addSphere(transform[3], averageScale, 10, 10, color);

        if (m_hasRing)
            aie::Gizmos::addRing(transform[3], 1.25f * averageScale, 1.75f * averageScale, 10, color);
    }

    for (auto moon : m_moons)
        moon->Draw();
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