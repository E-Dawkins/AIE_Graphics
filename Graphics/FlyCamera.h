#pragma once
#include "BaseCamera.h"

class FlyCamera : public BaseCamera
{
public:
    void Update(float _dt) override;
    
protected:
    vec2 m_lastMousePos = vec2(0);
};

