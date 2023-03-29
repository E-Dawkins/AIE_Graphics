#pragma once
#include "FlyCamera.h"

class OrbitalCamera : public BaseCamera
{
public:
	OrbitalCamera(mat4& _target, vec3 _targetOffset, float _orbitalSpeed = 0.01f);

	void Update(float _dt) override;
	
	void SetTarget(mat4 _target, vec3 _targetOffset);
	
protected:
	mat4 m_target;
	vec3 m_targetOffset;
	float m_orbitalSpeed;
};