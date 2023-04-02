#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <vector>

#include "BaseCamera.h"

class BaseCamera;
class Instance;

const int MAX_LIGHTS = 4;

struct Light
{
    Light()
    {
        direction = vec3(0);
        color = vec3(1);
        intensity = 1;
    }
    
    Light(vec3 _direction, vec3 _color, float _intensity)
    {
        direction = _direction;
        color = _color * _intensity;
        intensity = _intensity;
    }

    vec3 direction;
    vec3 color;
    float intensity;
};

class Scene
{
public:
    Scene(char* _sceneName, BaseCamera* _camera, vec2 _windowSize,
        Light& _light, vec3 _ambientLightColor);
    ~Scene();
    
    void Draw();
    void AddInstance(Instance* _instance)
    {
        m_instances.push_back(_instance);
    }
    void AddPointLight(Light& _light)
    {
        m_pointLights.push_back(_light);
    }
    void AddPointLight(vec3 _direction, vec3 _color, float _intensity)
    {
        m_pointLights.push_back(Light(_direction, _color, _intensity));
    }
    void AddCamera(BaseCamera* _camera)
    {
        m_cameras.push_back(_camera);
    }

    void ImGuiRefresher();
    void SetImGuiFunction(std::function<void()> _delegate) { m_delegate = _delegate; }

    char* GetSceneName()                    { return m_sceneName; }
    BaseCamera*& GetCamera()                { return m_cameras[m_activeCamera]; }
    glm::vec2 GetWindowSize()               { return m_windowSize; }
    glm::vec3& GetAmbientLightColor()       { return m_ambientLightColor; }
    Light& GetSunLight()                    { return m_sunLight; }
    std::vector<Light>& GetPointLights()    { return m_pointLights; }
    int GetNumberOfLights()                 { return m_pointLights.size(); }
    glm::vec3* GetPointLightPositions()     { return &m_pointLightPositions[0]; }
    glm::vec3* GetPointLightColors()        { return &m_pointLightColors[0]; }
    
protected:
    char*                       m_sceneName;
    vec2                        m_windowSize;

    int                         m_activeCamera;
    std::vector<BaseCamera*>    m_cameras;

    Light                       m_sunLight;
    std::vector<Light>          m_pointLights;
    
    glm::vec3                   m_ambientLightColor;
    std::vector<Instance*>      m_instances;

    glm::vec3                   m_pointLightPositions[MAX_LIGHTS];
    glm::vec3                   m_pointLightColors[MAX_LIGHTS];

    // ImGui stuff
    std::function<void()>       m_delegate;
};
