#pragma once
#include <glm/glm.hpp>

using glm::vec2;
using glm::vec3;
using glm::mat4;

class SimpleCamera
{
public:
    SimpleCamera();
    ~SimpleCamera() = default;

    virtual void Update(float _dt);\
    
    // Getters
    vec3 GetPosition() { return m_position; }
    mat4 GetViewMatrix();
    mat4 GetProjectionMatrix(float _width, float _height);
    mat4 GetTransform(vec3 _position, vec3 _eulerAngles, vec3 _scale);

    // Setters
    void SetPosition(vec3 _position) { m_position = _position; }
    
protected:
    mat4 m_projectionViewTransform;
    mat4 m_worldTransform;
    mat4 m_viewTransform;

    vec3 m_position;
    vec2 m_lastMousePos;
    
    float m_aspectRatio;
    
    float m_theta;
    float m_phi;

    float m_turnSpeed = glm::radians(180.f);
};

