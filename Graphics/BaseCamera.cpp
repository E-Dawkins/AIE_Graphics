#include "BaseCamera.h"

#include <Gizmos.h>

BaseCamera::BaseCamera()
{
    m_projectionViewTransform = mat4(1);
    m_worldTransform = mat4(1);
    m_viewTransform = mat4(1);
    
    m_aspectRatio = 16.f / 9.f;
    m_sensitivity = glm::radians(15.f);

    // Initialise post processing shader & quad
    m_postProcessing.shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/post.vert");
    m_postProcessing.shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/post.frag");

    if (!m_postProcessing.shader.link())
        printf("Post Process Shader Error!\n%s", m_postProcessing.shader.getLastError());

    m_postProcessing.screenQuad.InitialiseFullscreenQuad();
}

void BaseCamera::PostProcessDraw(aie::RenderTarget& _renderTarget)
{
    m_postProcessing.shader.bind();
    
    m_postProcessing.shader.bindUniform("colorTarget", 0);
    m_postProcessing.shader.bindUniform("depthTarget", 1);
    
    m_postProcessing.shader.bindUniform("postProcessTarget", m_postProcessing.currentEffect);
    m_postProcessing.shader.bindUniform("windowWidth", (int)ImGui::GetWindowWidth());
    m_postProcessing.shader.bindUniform("windowHeight", (int)ImGui::GetWindowHeight());
    m_postProcessing.shader.bindUniform("time", ImGui::GetTime());

    _renderTarget.getTarget(0).bind(0);
    _renderTarget.bindDepthTarget(1);

    m_postProcessing.screenQuad.Draw();
}

void BaseCamera::CameraImGui()
{
    /* --- Camera Settings --- */
	
    ImGui::Begin("Camera Settings");

    float tempSens = glm::degrees(GetSensitivity());
    ImGui::DragFloat("Sensitivity", &tempSens, 1.f, 5.f, 180.f);
    SetSensitivity(glm::radians(tempSens));
	
    ImGui::End();

    /* --- Post Processing --- */
	
    ImGui::Begin("Post Processing");
	
    std::vector<const char*> items;
	
    for (auto effect : m_postProcessing.effects)
        items.push_back(effect.first);

    ImGui::PushItemWidth(-1);

    static int itemIndex = 0;
    ImGui::ListBox("", &itemIndex, items.data(), items.size(), (int)items.size());

    m_postProcessing.currentEffect = m_postProcessing.effects[itemIndex].second;
	
    ImGui::End();
}

vec3 BaseCamera::GetPosition()
{
    return m_worldTransform[3];
}

mat4 BaseCamera::GetRotation()
{
    vec3 scale = GetScale();

    mat4 rotation =
    {
        m_worldTransform[0] / scale.x,
        m_worldTransform[1] / scale.y,
        m_worldTransform[2] / scale.z,
        m_worldTransform[3]
    };

    return rotation;
}

vec3 BaseCamera::GetScale()
{
    float xScale = length(vec3(m_worldTransform[0]));
    float yScale = length(vec3(m_worldTransform[1]));
    float zScale = length(vec3(m_worldTransform[2]));
    
    return { xScale, yScale, zScale };
}

vec3 BaseCamera::GetRight(mat4 _transform)
{
    return cross(vec3(_transform[1]), GetForward(_transform));
}

vec3 BaseCamera::GetUp(mat4 _transform)
{
    return cross(GetForward(_transform), GetRight(_transform));
}

vec3 BaseCamera::GetForward(mat4 _transform)
{
    mat4 inverted = inverse(_transform);
    vec3 forward = normalize(vec3(inverted[2]));

    return forward;
}

mat4 BaseCamera::GetProjectionMatrix()
{
    return glm::perspective(glm::pi<float>() * 0.25f, m_aspectRatio, 0.1f, 1000.f);
}

mat4 BaseCamera::GetWorldTransform(vec3 _position, vec3 _eulerAngles, vec3 _scale)
{
    mat4 translateMatrix = translate(mat4(1), _position);

    mat4 rotationMatrix = rotate(mat4(1), _eulerAngles.x, vec3(1, 0, 0));
    rotationMatrix = rotate(rotationMatrix, _eulerAngles.y, vec3(0, 1, 0));
    rotationMatrix = rotate(rotationMatrix, _eulerAngles.z, vec3(0, 0, 1));

    mat4 scaleMatrix = scale(mat4(1), _scale);
    
    return scaleMatrix * rotationMatrix * translateMatrix;
}

mat4 BaseCamera::GetProjectionViewMatrix()
{
    return GetProjectionMatrix() * GetViewMatrix();
}

mat4 BaseCamera::GetViewMatrix()
{
    return lookAt(GetPosition(), GetPosition() + GetForward(m_worldTransform), vec3(0, 1, 0));
}

float BaseCamera::GetAspectRatio()
{
    return m_aspectRatio;
}

float BaseCamera::GetSensitivity()
{
    return m_sensitivity;
}

mat4 BaseCamera::GetTransform()
{
    return m_worldTransform;
}

void BaseCamera::SetPosition(vec3 _position)
{
    m_worldTransform[3] = vec4(_position, 1);
}

void BaseCamera::SetRotation(vec3 _rotation)
{
    mat4 newMatrix = translate(mat4(1), GetPosition());
    
    newMatrix = rotate(newMatrix, _rotation.z, vec3(0, 0, 1));
    newMatrix = rotate(newMatrix, _rotation.y, vec3(0, 1, 0));
    newMatrix = rotate(newMatrix, _rotation.x, vec3(1, 0, 0));

    newMatrix = scale(newMatrix, GetScale());

    m_worldTransform = newMatrix;
}

void BaseCamera::SetAspectRatio(float _width, float _height)
{
    m_aspectRatio = _width / _height;
}

void BaseCamera::SetViewMatrix(vec3 _from, vec3 _to, vec3 _up)
{
    
}

void BaseCamera::SetProjectionMatrix(float _fieldOfView, float _aspectRatio, float _near, float _far)
{
    
}

void BaseCamera::SetProjectionMatrix(float _fieldOfView, float _width, float _height, float _near, float _far)
{
    
}

void BaseCamera::SetSensitivity(float _sensitivity)
{
    m_sensitivity = _sensitivity;
}