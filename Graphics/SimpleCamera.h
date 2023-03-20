#pragma once
#include <glm/glm.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class SimpleCamera
{
public:
    SimpleCamera();
    ~SimpleCamera() = default;

    virtual void Update(float _dt);
    
    // Getters
    vec3 GetPosition();
    vec3 GetScale();
    vec3 GetForward(mat4 _transform);
    vec3 GetRight(mat4 _transform);
    vec3 GetUp(mat4 _transform);
    mat4 GetWorldTransform(vec3 _position, vec3 _eulerAngles, vec3 _scale);
    mat4 GetProjectionViewMatrix();
    mat4 GetProjectionMatrix();
    mat4 GetViewMatrix();
    float GetAspectRatio();

    // Setters
    void SetPosition(vec3 _position);
    void SetAspectRatio(float _width, float _height);
    void SetViewMatrix(vec3 _from, vec3 _to, vec3 _up);
    void SetProjectionMatrix(float _fieldOfView, float _aspectRatio, float _near, float _far);
    void SetProjectionMatrix(float _fieldOfView, float _width, float _height, float _near, float _far);
    
protected:
    mat4 m_projectionViewTransform;
    mat4 m_worldTransform;
    mat4 m_viewTransform;
    
    vec2 m_lastMousePos;
    
    float m_aspectRatio;

    float m_turnSpeed;
};

