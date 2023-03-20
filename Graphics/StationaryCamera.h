#pragma once
#include "SimpleCamera.h"

class StationaryCamera : public SimpleCamera
{
public:
    StationaryCamera(vec3 _position, vec3 _rotation);
    
    void Update(float _dt) override { }
    
    void SetRotation(vec3 _rotation);
};

