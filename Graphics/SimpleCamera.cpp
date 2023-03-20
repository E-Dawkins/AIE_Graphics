#include "SimpleCamera.h"

#include <imgui.h>
#include <Input.h>
#include <glm/ext.hpp>

SimpleCamera::SimpleCamera()
{
    m_position = vec3(-10, 2, 0);
    m_theta = 0;
    m_phi = 0;
    m_lastMousePos = vec2(0);
}

void SimpleCamera::Update(float _dt)
{
    aie::Input* input = aie::Input::getInstance();

    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);

    vec3 forward(glm::cos(phiR) * glm::cos(thetaR), sin(phiR),
                   glm::cos(phiR) * glm::sin(thetaR));
    vec3 right(-sin(thetaR), 0, glm::cos(thetaR));
    vec3 up(0, 1, 0);

    // We will use WASD to move and the Q & E to go up and down
    if (input->isKeyDown(aie::INPUT_KEY_W))
        m_position += forward * _dt;
    if (input->isKeyDown(aie::INPUT_KEY_S))
        m_position -= forward * _dt;
    if (input->isKeyDown(aie::INPUT_KEY_D))
        m_position += right * _dt;
    if (input->isKeyDown(aie::INPUT_KEY_A))
        m_position -= right * _dt;

    if (input->isKeyDown(aie::INPUT_KEY_Q))
        m_position += up * _dt;
    if (input->isKeyDown(aie::INPUT_KEY_E))
        m_position -= up * _dt;

    // Get the mouse coordinates
    float mx = input->getMouseX();
    float my = input->getMouseY();

    // If RMB held down, increment theta and phi (rotate)
    if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
    {
        m_theta += m_turnSpeed * (mx - m_lastMousePos.x) * _dt;
        m_phi += m_turnSpeed * (my - m_lastMousePos.y) * _dt;
    }

    m_lastMousePos = vec2(mx, my);
}

mat4 SimpleCamera::GetViewMatrix()
{
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);
    vec3 forward(glm::cos(phiR) * glm::cos(thetaR), sin(phiR),
                 glm::cos(phiR) * glm::sin(thetaR));
    
    return lookAt(m_position, m_position + forward, vec3(0, 1, 0));
}

mat4 SimpleCamera::GetProjectionMatrix(float _width, float _height)
{
    return glm::perspective(glm::pi<float>() * 0.25f, _width / _height,
                            0.1f, 1000.f);
}

mat4 SimpleCamera::GetTransform(vec3 _position, vec3 _eulerAngles, vec3 _scale)
{
    mat4 translateMatrix = translate(mat4(1), _position);

    mat4 rotationMatrix = rotate(mat4(1), _eulerAngles.x, vec3(1, 0, 0));
    rotationMatrix = rotate(rotationMatrix, _eulerAngles.y, vec3(0, 1, 0));
    rotationMatrix = rotate(rotationMatrix, _eulerAngles.z, vec3(0, 0, 1));

    mat4 scaleMatrix = scale(mat4(1), _scale);
    
    return scaleMatrix * rotationMatrix * translateMatrix;
}
