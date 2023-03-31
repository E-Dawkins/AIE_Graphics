#include "Scene.h"

#include <Gizmos.h>

#include "Instance.h"
#include "FlyCamera.h"

Scene::Scene(char* _sceneName, BaseCamera& _camera, vec2 _windowSize, Light& _light, vec3 _ambientLightColor)
{
    m_sceneName = _sceneName;
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

        aie::Gizmos::addSphere(m_pointLights[i].direction, 0.05f, 8, 8, vec4(m_pointLights[i].color, 1));
    }
    
    for (auto it = m_instances.begin(); it != m_instances.end(); it++)
    {
        Instance* instance = *it;
        instance->Draw(this);
    }
}

