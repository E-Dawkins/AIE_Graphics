#pragma once

#include <vector>

#include "Application.h"
#include <glm/mat4x4.hpp>

#include "Planet.h"

class GraphicsApp : public aie::Application {
public:

	GraphicsApp();
	virtual ~GraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void CreatePlanets();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	std::vector<Planet*> m_planets;
};
