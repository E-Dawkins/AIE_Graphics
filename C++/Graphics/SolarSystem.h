#pragma once
#include "Scene.h"

#include "Planet.h"
#include "FlyCamera.h"

#include <vector>

class SolarSystem
{
public:
    SolarSystem();
    
    void Start();
    void Update(float _dt);
    void Draw();
    void ImGuiRefresher();

protected:
    vec4 GetMatrixPosition(mat4 _matrix) { return _matrix[3]; }
    
    std::vector<Planet*> m_planets;

    float m_solarSystemSpeed;

    FlyCamera* m_camera;
};
