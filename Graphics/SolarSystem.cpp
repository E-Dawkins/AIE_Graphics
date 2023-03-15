#include "SolarSystem.h"

void SolarSystem::Start()
{
    float earthRadians = 0.01f;

    // Sun
    m_planets.push_back(new Planet(vec3(0), 3, vec4(1, 0.3, 0, 1), 0.1f));

    // Mercury
    m_planets.push_back(new Planet(vec3(4, 0, 0), 0.35f, vec4(1, 0.8, 0.5, 1), earthRadians * (365.f / 88.f)));

    // Venus
    m_planets.push_back(new Planet(vec3(5, 0, 0), 0.4f, vec4(1, 0.8, 0.2, 1), earthRadians * (365.f / 225.f)));

    // Earth
    m_planets.push_back(new Planet(vec3(6, 0, 0), 0.5f, vec4(0, 0.6, 0.7, 1), earthRadians));

    // Moon
    m_planets.push_back(new Planet(vec3(1, 0, 0), 0.1f, vec4(1), earthRadians * (365.f / 27.f), m_planets.back()));

    // Mars
    m_planets.push_back(new Planet(vec3(8, 0, 0), 0.3f, vec4(1, 0.2, 0.2, 1), earthRadians * (365.f / 687.f)));

    // Jupiter
    m_planets.push_back(new Planet(vec3(9, 0, 0), 0.65f, vec4(1, 0.4, 0, 1), earthRadians * (365.f / 4333.f)));

    // Saturn
    m_planets.push_back(new Planet(vec3(11, 0, 0), 0.7f, vec4(1, 0.8, 0, 1), earthRadians * (365.f / 10759.f)));
    m_planets.back()->HasRing(true);
	
    // Uranus
    m_planets.push_back(new Planet(vec3(13, 0, 0), 0.7f, vec4(0, 0.6, 1, 1), earthRadians * (365.f / 30687.f)));

    // Neptune
    m_planets.push_back(new Planet(vec3(15, 0, 0), 0.7f, vec4(0, 0.3, 1, 1), earthRadians * (365.f / 60190.f)));
}

void SolarSystem::Update(float _dt)
{
    // Update planets
    for (auto planet : m_planets)
        planet->Update(_dt);
}

void SolarSystem::Draw()
{
    // Draw planets
    for (auto planet : m_planets)
        planet->Draw();
}
