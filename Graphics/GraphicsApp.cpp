#include "GraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

GraphicsApp::GraphicsApp() = default;
GraphicsApp::~GraphicsApp() = default;

bool GraphicsApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = lookAt(vec3(20), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	// CreatePlanets();
	
	return LaunchShaders();
}

void GraphicsApp::shutdown() {

	Gizmos::destroy();
}

void GraphicsApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// Update planets
	for (auto planet : m_planets)
		planet->Update(deltaTime);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GraphicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	// Draw planets
	for (auto planet : m_planets)
		planet->Draw();

#pragma region SimpleShader
	// Bind the shader
	m_simpleShader.bind();

	// Bind the transform

	auto pvm = m_projectionMatrix * m_viewMatrix * m_quadTransform;
	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Draw the quad using Mesh's draw
	m_quadMesh.Draw();
	
#pragma endregion
	
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}

void GraphicsApp::CreatePlanets()
{
	float earthRadians = 0.01f;
	float moonRadians = 0.1f;

	// Sun
	m_planets.push_back(new Planet(vec3(0), 3, vec4(1, 0.3, 0, 1), 0.1f));

	// Mercury
	m_planets.push_back(new Planet(vec3(4, 0, 0), 0.35f, vec4(1, 0.8, 0.5, 1), earthRadians * (365.f / 88.f)));

	// Venus
	m_planets.push_back(new Planet(vec3(5, 0, 0), 0.4f, vec4(1, 0.8, 0.2, 1), earthRadians * (365.f / 225.f)));

	// Earth
	m_planets.push_back(new Planet(vec3(6, 0, 0), 0.5f, vec4(0, 0.6, 0.7, 1), earthRadians));

	// Moon
	m_planets.push_back(new Planet(vec3(0), 0.1f, vec4(1), moonRadians, m_planets.back()));

	// Mars
	m_planets.push_back(new Planet(vec3(8, 0, 0), 0.3f, vec4(1, 0.2, 0.2, 1), earthRadians * (365.f / 687.f)));

	// Jupiter
	m_planets.push_back(new Planet(vec3(9, 0, 0), 0.65f, vec4(1, 0.4, 0, 1), earthRadians * (365.f / 4333.f)));

	// Saturn
	m_planets.push_back(new Planet(vec3(11, 0, 0), 0.7f, vec4(1, 0.8, 0, 1), earthRadians * (365.f / 10759.f)));

	// Uranus
	m_planets.push_back(new Planet(vec3(13, 0, 0), 0.7f, vec4(0, 0.6, 1, 1), earthRadians * (365.f / 30687.f)));

	// Neptune
	m_planets.push_back(new Planet(vec3(15, 0, 0), 0.7f, vec4(0, 0.3, 1, 1), earthRadians * (365.f / 60190.f)));
}

bool GraphicsApp::LaunchShaders()
{
	// Load the simple vert and frag shaders into the m_simpleShader variable
	m_simpleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (!m_simpleShader.link())
	{
		printf("Simple Shader has an Error: %s\n", m_simpleShader.getLastError());
		return false;
	}

	m_quadMesh.InitialiseQuad();

	// This is a 10 'unit' wide quad
	m_quadTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1
	};
	
	return true;
}
