#pragma once
#include "FlyCamera.h"

class StationaryCamera : public BaseCamera
{
public:
    StationaryCamera() = default;
    StationaryCamera(vec3 _position, vec3 _rotation);
};

