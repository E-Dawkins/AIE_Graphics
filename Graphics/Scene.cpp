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
    // Draw cylinders for each camera
    for (auto cam : m_cameras)
    {
        if (cam != GetCamera()) // don't draw gizmo for active cam
        {
            aie::Gizmos::addCylinderFilled(cam->GetPosition(),
                0.1f, 0.15f, 10, vec4(0, 1, 0, 1));
        }
    }
    
    for (int i = 0; i < MAX_LIGHTS && i < m_pointLights.size(); i++)
    {
        m_pointLightPositions[i] = m_pointLights[i].direction;
        m_pointLightColors[i] = m_pointLights[i].color;

        aie::Gizmos::addSphere(m_pointLights[i].direction, 0.05f, 8, 8, vec4(m_pointLights[i].color, 1));
    }
    
    for (auto it = m_instances.begin(); it != m_instances.end(); it++)
    {
        Instance* instance = *it;

        if (instance->isActive)
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

    /* --- Instance Transforms --- */

    ImGui::Begin("Instance Settings");

    for (int i = 0; i < m_instances.size(); i++)
    {
        std::string iString = std::to_string(i);
        
        if (ImGui::CollapsingHeader(iString.c_str()))
        {
            // Position
            ImGui::DragFloat3((iString + " : Position").c_str(),
                &m_instances[i]->GetTransform()[3][0], 0.05f);

            // Scale
            vec3 newScale = m_instances[i]->GetScale();
            ImGui::DragFloat3((iString + " : Scale").c_str(),
                &newScale[0], 0.05f);
            m_instances[i]->SetScale(newScale);

            // Is Active
            ImGui::Checkbox((iString + " : Enabled").c_str(), &m_instances[i]->isActive);
        }
    }
    
    ImGui::End();

    /* ImGui Delegate */
    
    m_delegate();
}

