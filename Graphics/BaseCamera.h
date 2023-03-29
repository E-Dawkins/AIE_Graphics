#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class BaseCamera
{
public:
    BaseCamera();
    virtual ~BaseCamera() = default;

    virtual void Update(float _dt) {}

    // Getters
    vec3 GetPosition();
    mat4 GetRotation();
    vec3 GetScale();
    vec3 GetRight(mat4 _transform);
    vec3 GetUp(mat4 _transform);
    vec3 GetForward(mat4 _transform);
    mat4 GetWorldTransform(vec3 _position, vec3 _eulerAngles, vec3 _scale);
    mat4 GetProjectionViewMatrix();
    mat4 GetProjectionMatrix();
    mat4 GetViewMatrix();
    float GetAspectRatio();
    float GetSensitivity();
    mat4 GetTransform();
    
    // Setters
    void SetPosition(vec3 _position);
    void SetRotation(vec3 _rotation);
    void SetAspectRatio(float _width, float _height);
    void SetViewMatrix(vec3 _from, vec3 _to, vec3 _up);
    void SetProjectionMatrix(float _fieldOfView, float _aspectRatio, float _near, float _far);
    void SetProjectionMatrix(float _fieldOfView, float _width, float _height, float _near, float _far);
    void SetSensitivity(float _sensitivity);

protected:
    mat4 m_projectionViewTransform;
    mat4 m_worldTransform;
    mat4 m_viewTransform;

    float m_sensitivity;
    float m_aspectRatio;
};

