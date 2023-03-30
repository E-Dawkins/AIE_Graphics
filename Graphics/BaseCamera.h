#pragma once
#include <imgui.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Mesh.h"
#include "RenderTarget.h"
#include "Shader.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

struct PostProcessing
{
    std::vector<std::pair<const char*, int>> effects =
    {
        {"Default",			-1},
        {"Box Blur",		0},
        {"Gaussian Blur",	1},
        {"Distort",			2},
        {"Edge Detection",	3},
        {"Sepia",			4},
        {"Scanlines",		5},
        {"Grayscale",		6},
        {"Invert",			7},
        {"Pixelization",	8},
        {"Posterization",	9},
        {"Distance Fog",	10},
        {"Depth of Field",	11},
        {"Vignette",		12}
    };
    
    aie::ShaderProgram  shader;
    Mesh                screenQuad;
    int                 currentEffect = effects[0].second;
};

class BaseCamera
{
public:
    BaseCamera();
    virtual ~BaseCamera() = default;

    virtual void Update(float _dt) {}

    void PostProcessLoad();
    void PostProcessDraw(aie::RenderTarget& _renderTarget);

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
    PostProcessing& GetPostProcessing();
    
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
    
    PostProcessing m_postProcessing = PostProcessing();
};

