#include "FlyCamera.h"

#include <Input.h>

void FlyCamera::Update(float _dt)
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