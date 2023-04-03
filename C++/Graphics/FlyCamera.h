#pragma once
#include "BaseCamera.h"

class FlyCamera : public BaseCamera
{
public:
    FlyCamera() = default;
    FlyCamera(vec3 _position, vec3 _rotation = vec3(0));
    void Update(float _dt) override;
    
protected:
    vec2 m_lastMousePos = vec2(0);
};

