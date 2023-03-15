#pragma once

#include <vector>

#include "Application.h"
#include <glm/mat4x4.hpp>

#include "Planet.h"

#include "Mesh.h"
#include "Shader.h"
#include "OBJMesh.h"

class GraphicsApp : public aie::Application {
public:

	GraphicsApp();
	virtual ~GraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();


protected:

	void CreatePlanets();
	
	bool LaunchShaders();
	
	bool QuadLoader();
	void QuadDraw(mat4 _pvm);
	
	bool BunnyLoader();
	void BunnyDraw(mat4 _pvm);
	
	// camera transforms
	mat4 m_viewMatrix;
	mat4 m_projectionMatrix;

	std::vector<Planet*> m_planets;

	aie::ShaderProgram	m_simpleShader;
	aie::ShaderProgram	m_colorShader;
	
	Mesh				m_quadMesh;
	mat4				m_quadTransform;

	aie::OBJMesh		m_bunnyMesh;
	mat4				m_bunnyTransform;
};
