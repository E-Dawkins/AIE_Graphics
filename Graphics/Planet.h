#pragma once
#include <vector>
#include <glm/glm.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Planet
{
public:
    Planet(char* _name, vec3 _center, float _radius, vec4 _color, float _radians, Planet* _parent = nullptr);
    ~Planet();
    
    void Update(float _dt);
    void Draw();

    mat4 RotateAround(vec3 _point, vec3 _axis, float _radians);

    void HasRing(bool _hasRing);
    float GetAverageScale(mat4 _transform);

    void SetRotationMultiplier(float _multiplier)
    {
        for (auto moon : m_moons)
            moon->SetRotationMultiplier(_multiplier);
        
        m_rotationMultiplier = _multiplier;
    }

    void AddMoon(Planet* _moon) { m_moons.push_back(_moon); }
    std::vector<Planet*>& GetMoons() { return m_moons; }
    
    char* name;
    mat4 transform;
    bool isVisible;
    
    vec4 color;
    
protected:
    Planet* m_parent;
    std::vector<Planet*> m_moons;
    
    float m_rotationRadians;
    float m_rotationMultiplier;

    bool m_hasRing;
};
