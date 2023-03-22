#include "Scene.h"

#include "Instance.h"
#include "SimpleCamera.h"

Scene::Scene(SimpleCamera& _camera, vec2 _windowSize, Light& _light, vec3 _ambientLightColor)
{
    m_camera = &_camera;
    m_windowSize = _windowSize;
    m_light = _light;
    m_ambientLightColor = _ambientLightColor;
}

Scene::~Scene()
{
    for (auto it = m_instances.begin(); it != m_instances.end(); it++)
    {
        delete* it;
    }
}

void Scene::AddInstance(Instance* _instance)
{
    m_instances.push_back(_instance);
}

void Scene::Draw()
{
    for (int i = 0; i < MAX_LIGHTS && i < m_pointLights.size(); i++)
    {
        m_pointLightPositions[i] = m_pointLights[i].direction;
        m_pointLightColors[i] = m_pointLights[i].color;
    }
    
    for (auto it = m_instances.begin(); it != m_instances.end(); it++)
    {
        Instance* instance = *it;
        instance->Draw(this);
    }
}

