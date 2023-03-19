#pragma once
#include <vector>

#include "Planet.h"
#include "Scene.h"

class SolarSystem : public Scene
{
public:
    SolarSystem();
    
    void Start() override;
    void Update(float _dt) override;
    void Draw() override;
    void ImGuiRefresher() override;

protected:
    vec4 GetMatrixPosition(mat4 _matrix) { return _matrix[3]; }
    
    std::vector<Planet*> m_planets;

    float m_solarSystemSpeed;
};
