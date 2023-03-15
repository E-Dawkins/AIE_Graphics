#pragma once
#include <vector>

#include "Planet.h"
#include "Scene.h"

class SolarSystem : public Scene
{
public:
    void Start() override;
    void Update(float _dt) override;
    void Draw() override;

protected:
    std::vector<Planet*> m_planets;
};
