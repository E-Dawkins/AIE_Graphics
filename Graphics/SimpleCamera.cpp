#include "SimpleCamera.h"

#include <imgui.h>
#include <Input.h>
#include <glm/ext.hpp>

SimpleCamera::SimpleCamera()
{
    m_projectionViewTransform = mat4(1);
    m_worldTransform = mat4(1);
    m_viewTransform = mat4(1);
    m_lastMousePos = vec2(0);
    m_aspectRatio = 16.f / 9.f;

    m_sensitivity = glm::radians(15.f);
}

void SimpleCamera::Update(float _dt)
{
    aie::Input* input = aie::Input::getInstance();

    vec3 forward = GetForward(m_worldTransform);
    vec3 right = GetRight(m_worldTransform);
    vec3 up = GetUp(m_worldTransform);

    float moveSpeed = 1.f;

    if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
        moveSpeed = 3.f;
    
    // We will use WASD to move and the Q & E to go up and down
    if (input->isKeyDown(aie::INPUT_KEY_W))
        SetPosition(GetPosition() + forward * moveSpeed * _dt);
    if (input->isKeyDown(aie::INPUT_KEY_S))
        SetPosition(GetPosition() - forward * moveSpeed * _dt);
    if (input->isKeyDown(aie::INPUT_KEY_D))
        SetPosition(GetPosition() - right * moveSpeed * _dt);
    if (input->isKeyDown(aie::INPUT_KEY_A))
        SetPosition(GetPosition() + right * moveSpeed * _dt);

    if (input->isKeyDown(aie::INPUT_KEY_E))
        SetPosition(GetPosition() + up * moveSpeed * _dt);
    if (input->isKeyDown(aie::INPUT_KEY_Q))
        SetPosition(GetPosition() - up * moveSpeed * _dt);
    
    // Get the mouse coordinates
    float mx = input->getMouseX();
    float my = input->getMouseY();
    
    // If RMB held down, increment theta and phi (rotate)
    if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
    {
        m_worldTransform = rotate(m_worldTransform, m_sensitivity * (mx - m_lastMousePos.x) * _dt, GetUp(m_worldTransform));
        m_worldTransform = rotate(m_worldTransform, m_sensitivity * (my - m_lastMousePos.y) * _dt, GetRight(m_worldTransform));
    }

    m_lastMousePos = vec2(mx, my);
}

vec3 SimpleCamera::GetPosition()
{
    return m_worldTransform[3];
}

vec3 SimpleCamera::GetScale()
{
    float xScale = length(vec3(m_worldTransform[0]));
    float yScale = length(vec3(m_worldTransform[1]));
    float zScale = length(vec3(m_worldTransform[2]));
    
    return { xScale, yScale, zScale };
}

vec3 SimpleCamera::GetRight(mat4 _transform)
{
    mat4 inverted = inverse(_transform);
    vec3 right = normalize(vec3(inverted[0]));

    return right;
}

vec3 SimpleCamera::GetUp(mat4 _transform)
{
    mat4 inverted = inverse(_transform);
    vec3 up = normalize(vec3(inverted[1]));

    return up;
}

vec3 SimpleCamera::GetForward(mat4 _transform)
{
    mat4 inverted = inverse(_transform);
    vec3 forward = normalize(vec3(inverted[2]));

    return forward;
}

mat4 SimpleCamera::GetProjectionMatrix()
{
    return glm::perspective(glm::pi<float>() * 0.25f, m_aspectRatio, 0.1f, 1000.f);
}

mat4 SimpleCamera::GetWorldTransform(vec3 _position, vec3 _eulerAngles, vec3 _scale)
{
    mat4 translateMatrix = translate(mat4(1), _position);

    mat4 rotationMatrix = rotate(mat4(1), _eulerAngles.x, vec3(1, 0, 0));
    rotationMatrix = rotate(rotationMatrix, _eulerAngles.y, vec3(0, 1, 0));
    rotationMatrix = rotate(rotationMatrix, _eulerAngles.z, vec3(0, 0, 1));

    mat4 scaleMatrix = scale(mat4(1), _scale);
    
    return scaleMatrix * rotationMatrix * translateMatrix;
}

mat4 SimpleCamera::GetProjectionViewMatrix()
{
    return GetProjectionMatrix() * GetViewMatrix();
}

mat4 SimpleCamera::GetViewMatrix()
{
    return lookAt(GetPosition(), GetPosition() + GetForward(m_worldTransform), vec3(0, 1, 0));
}

float SimpleCamera::GetAspectRatio()
{
    return m_aspectRatio;
}

float SimpleCamera::GetSensitivity()
{
    return m_sensitivity;
}

void SimpleCamera::SetPosition(vec3 _position)
{
    m_worldTransform[3] = vec4(_position, 1);
}

void SimpleCamera::SetAspectRatio(float _width, float _height)
{
    m_aspectRatio = _width / _height;
}

void SimpleCamera::SetViewMatrix(vec3 _from, vec3 _to, vec3 _up)
{
    
}

void SimpleCamera::SetProjectionMatrix(float _fieldOfView, float _aspectRatio, float _near, float _far)
{
    
}

void SimpleCamera::SetProjectionMatrix(float _fieldOfView, float _width, float _height, float _near, float _far)
{
    
}

void SimpleCamera::SetSensitivity(float _sensitivity)
{
    m_sensitivity = _sensitivity;
}
