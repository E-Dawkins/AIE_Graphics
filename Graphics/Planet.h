#pragma once
#include <glm/glm.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Planet
{
public:
    Planet(vec3 _center, float _radius, vec4 _color, float _radians, Planet* _parent = nullptr);
    ~Planet();
    
    void Update(float _dt);
    void Draw();

    mat4 RotateAround(vec3 _point, vec3 _axis, float _radians);


    void HasRing(bool _hasRing);
    float GetAverageScale(mat4 _transform);

    mat4 transform;
    
protected:
    vec4 m_color;
    float m_rotationRadians;
    Planet* m_parent;
    
    bool m_hasRing;
};
