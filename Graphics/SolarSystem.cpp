#include "SolarSystem.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

SolarSystem::SolarSystem()
{
    m_solarSystemSpeed = 1.f;
}

void SolarSystem::Start()
{
    float earthRadians = 0.001f;

    // Sun
    m_planets.push_back(new Planet("Sun", vec3(0), 1.5f, vec4(1, 0.3, 0, 1), 0.f));

    // Mercury
    m_planets.push_back(new Planet("Mercury", vec3(4, 0, 0), 0.24f, vec4(1, 0.8, 0.5, 1), earthRadians * (365.f / 88.f), m_planets.front()));

    // Venus
    m_planets.push_back(new Planet("Venus", vec3(5, 0, 0), 0.26f, vec4(1, 0.8, 0.2, 1), earthRadians * (365.f / 225.f), m_planets.front()));

    // Earth
    m_planets.push_back(new Planet("Earth", vec3(6, 0, 0), 0.34f, vec4(0, 0.6, 0.7, 1), earthRadians, m_planets.front()));

    // Moon
    m_planets.back()->AddMoon(new Planet("Moon", vec3(1, 0, 0), 0.25f, vec4(1), earthRadians * (365.f / 27.f), m_planets.back()));

    // Mars
    m_planets.push_back(new Planet("Mars", vec3(8, 0, 0), 0.2f, vec4(1, 0.2, 0.2, 1), earthRadians * (365.f / 687.f), m_planets.front()));

    // Jupiter
    m_planets.push_back(new Planet("Jupiter", vec3(9, 0, 0), 0.44f, vec4(1, 0.4, 0, 1), earthRadians * (365.f / 4333.f), m_planets.front()));

    // Saturn
    m_planets.push_back(new Planet("Saturn", vec3(11, 0, 0), 0.36f, vec4(1, 0.8, 0, 1), earthRadians * (365.f / 10759.f), m_planets.front()));
    m_planets.back()->HasRing(true);
	
    // Uranus
    m_planets.push_back(new Planet("Uranus", vec3(13, 0, 0), 0.36f, vec4(0, 0.6, 1, 1), earthRadians * (365.f / 30687.f), m_planets.front()));

    // Neptune
    m_planets.push_back(new Planet("Neptune", vec3(15, 0, 0), 0.36f, vec4(0, 0.3, 1, 1), earthRadians * (365.f / 60190.f), m_planets.front()));
}

void SolarSystem::Update(float _dt)
{
    // Update planets
    for (auto planet : m_planets)
    {
        planet->SetRotationMultiplier(m_solarSystemSpeed);
        planet->Update(_dt);
    }
}

void SolarSystem::Draw()
{
    // Draw planets
    for (auto planet : m_planets)
        planet->Draw();
}

void SolarSystem::ImGuiRefresher()
{
    ImGui::Begin("Solar System Settings");

    ImGui::SliderFloat("Solar System Speed", &m_solarSystemSpeed, 0.01f, 50.f);
    ImGui::DragFloat3("World Position", &m_planets.front()->transform[3][0], 0.05f);

    static vec3 worldRotation = vec3(0);
    static mat4 worldMatrix = mat4(1);

    float DEG2RAD = glm::pi<float>() / 180.f;
    
    worldMatrix = rotate(worldMatrix, worldRotation.x * DEG2RAD, vec3(1, 0, 0));
    worldMatrix = rotate(worldMatrix, worldRotation.y * DEG2RAD, vec3(0, 1, 0));
    worldMatrix = rotate(worldMatrix, worldRotation.z * DEG2RAD, vec3(0, 0, 1));

    m_planets.front()->transform = worldMatrix * m_planets.front()->transform;
    
    ImGui::DragFloat3("World Rotation", &worldRotation[0], 0.1f, 0, 360);
    
    ImGui::Separator();
    
    for (auto planet : m_planets)
    {
        if (ImGui::CollapsingHeader(planet->name))
        {
            ImGui::Indent();
            
            ImGui::Checkbox("Visible", &planet->isVisible);
            ImGui::ColorEdit3("Color", &planet->color[0]);

            ImGui::Spacing();
            
            if (!planet->GetMoons().empty() && ImGui::CollapsingHeader("Moons"))
            {
                for (auto moon : planet->GetMoons())
                {
                    ImGui::Indent();
                    ImGui::Checkbox(moon->name, &moon->isVisible);
                    ImGui::Unindent();

                    ImGui::Separator();
                }
            }

            ImGui::Unindent();
        }

        ImGui::Separator();
    }

    ImGui::End();
}
