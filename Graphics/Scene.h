#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <list>

class SimpleCamera;
class Instance;

const int MAX_LIGHTS = 4;

struct Light
{
    Light()
    {
        direction = glm::vec3(0);
        color = glm::vec3(1);
    }
    
    Light(glm::vec3 _direction, glm::vec3 _color, float _intensity)
    {
        direction = _direction;
        color = _color * _intensity;
    }

    glm::vec3 direction;
    glm::vec3 color;
};

class Scene
{
public:
    Scene(SimpleCamera& _camera, glm::vec2 _windowSize,
        Light& _light, glm::vec3 _ambientLightColor);
    ~Scene();
    
    void AddInstance(Instance* _instance);
    void Draw();
    void AddPointLights(Light& _light)
    {
        m_pointLights.push_back(_light);
    }
    void AddPointLights(glm::vec3 _direction, glm::vec3 _color, float _intensity)
    {
        m_pointLights.push_back(Light(_direction, _color, _intensity));
    }

    SimpleCamera* GetCamera()               { return m_camera; }
    glm::vec2 GetWindowSize()               { return m_windowSize; }
    glm::vec3& GetAmbientLightColor()       { return m_ambientLightColor; }
    Light& GetLight()                       { return m_light; }
    std::vector<Light>& GetPointLights()    { return m_pointLights; }
    int GetNumberOfLights()                 { return m_pointLights.size(); }
    glm::vec3* GetPointLightPositions()     { return &m_pointLightPositions[0]; }
    glm::vec3* GetPointLightColors()        { return &m_pointLightColors[0]; }
    
protected:
    SimpleCamera*           m_camera;
    glm::vec2               m_windowSize;

    Light                   m_sunLight;
    std::vector<Light>      m_pointLights;
    
    Light                   m_light;
    glm::vec3               m_ambientLightColor;
    std::list<Instance*>    m_instances;

    glm::vec3 m_pointLightPositions[MAX_LIGHTS];
    glm::vec3 m_pointLightColors[MAX_LIGHTS];
};
