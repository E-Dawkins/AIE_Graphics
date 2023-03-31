#include "Scene.h"

#include <Gizmos.h>

#include "Instance.h"
#include "FlyCamera.h"

Scene::Scene(char* _sceneName, BaseCamera* _camera, vec2 _windowSize, Light& _light, vec3 _ambientLightColor)
{
    m_sceneName = _sceneName;
    m_windowSize = _windowSize;
    m_sunLight = _light;
    m_ambientLightColor = _ambientLightColor;
    
    m_cameras.push_back(_camera);
    m_activeCamera = 0;
}

Scene::~Scene()
{
    // Delete instances
    for (auto it = m_instances.begin(); it != m_instances.end(); it++)
    {
        delete* it;
    }

    // Delete cameras
    for (auto it = m_cameras.begin(); it != m_cameras.end(); ++it)
    {
        delete &it;
    }
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

void Scene::ImGuiRefresher()
{
    /* --- Camera Settings --- */
	
    ImGui::Begin("Camera Settings");

    float tempSens = glm::degrees(GetCamera()->GetSensitivity());
    ImGui::DragFloat("Sensitivity", &tempSens, 1.f, 5.f, 180.f);
    GetCamera()->SetSensitivity(glm::radians(tempSens));

    ImGui::Separator();
    
    ImGui::InputInt("Active Camera", &m_activeCamera);
    
    m_activeCamera = m_activeCamera % m_cameras.size();
    if (m_activeCamera < 0) m_activeCamera = m_cameras.size() - 1;
	
    ImGui::End();

    /* --- Post Processing --- */
    
    std::string activeCam = std::to_string(m_activeCamera);
    
    ImGui::Begin(("Post Processing : " + activeCam).c_str());
	
    std::vector<const char*> items;
	
    for (auto effect : GetCamera()->GetPostProcessing().effects)
        items.push_back(effect.first);

    ImGui::PushItemWidth(-1);
    
    ImGui::ListBox(activeCam.c_str(), &GetCamera()->GetPostProcessing().effectIndex,
        items.data(), items.size(), (int)items.size());
	
    ImGui::End();

    /* ImGui Delegate */
    
    m_delegate();
}

