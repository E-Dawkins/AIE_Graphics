#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <list>

class SimpleCamera;
class Instance;

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
    Scene(SimpleCamera* _camera, glm::vec2 _windowSize,
        Light& _light, glm::vec3 _ambientLightColor);
    ~Scene();
    
    void AddInstance(Instance* _instance);

    void Draw();

    SimpleCamera* GetCamera()           { return m_camera; }
    glm::vec2 GetWindowSize()           { return m_windowSize; }
    glm::vec3 GetAmbientLightColor()    { return m_ambientLightColor; }
    Light& GetLight()                    { return m_light; }

protected:
    SimpleCamera*           m_camera;
    glm::vec2               m_windowSize;
    Light                   m_light;
    glm::vec3               m_ambientLightColor;
    std::list<Instance*>    m_instances;
};
