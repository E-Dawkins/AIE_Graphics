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

	CreatePlanets();
	
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

	auto pv = m_projectionMatrix * m_viewMatrix;
	
	// Draw the quad
	QuadDraw(pv * m_quadTransform);

	// Draw the bunny
	BunnyDraw(pv * m_bunnyTransform);
	
	Gizmos::draw(pv);
}

void GraphicsApp::CreatePlanets()
{
	float earthRadians = 0.01f;

	// Sun
	m_planets.push_back(new Planet(vec3(0), 3, vec4(1, 0.3, 0, 1), 0.1f));

	// Mercury
	m_planets.push_back(new Planet(vec3(4, 0, 0), 0.35f, vec4(1, 0.8, 0.5, 1), earthRadians * (365.f / 88.f)));

	// Venus
	m_planets.push_back(new Planet(vec3(5, 0, 0), 0.4f, vec4(1, 0.8, 0.2, 1), earthRadians * (365.f / 225.f)));

	// Earth
	m_planets.push_back(new Planet(vec3(6, 0, 0), 0.5f, vec4(0, 0.6, 0.7, 1), earthRadians));

	// Moon
	m_planets.push_back(new Planet(vec3(1, 0, 0), 0.1f, vec4(1), earthRadians * (365.f / 27.f), m_planets.back()));

	// Mars
	m_planets.push_back(new Planet(vec3(8, 0, 0), 0.3f, vec4(1, 0.2, 0.2, 1), earthRadians * (365.f / 687.f)));

	// Jupiter
	m_planets.push_back(new Planet(vec3(9, 0, 0), 0.65f, vec4(1, 0.4, 0, 1), earthRadians * (365.f / 4333.f)));

	// Saturn
	m_planets.push_back(new Planet(vec3(11, 0, 0), 0.7f, vec4(1, 0.8, 0, 1), earthRadians * (365.f / 10759.f)));
	m_planets.back()->HasRing(true);
	
	// Uranus
	m_planets.push_back(new Planet(vec3(13, 0, 0), 0.7f, vec4(0, 0.6, 1, 1), earthRadians * (365.f / 30687.f)));

	// Neptune
	m_planets.push_back(new Planet(vec3(15, 0, 0), 0.7f, vec4(0, 0.3, 1, 1), earthRadians * (365.f / 60190.f)));
}

bool GraphicsApp::LaunchShaders()
{
	if (!QuadLoader())
		return false;

	if (!BunnyLoader())
		return false;
	
	return true;
}

bool GraphicsApp::QuadLoader()
{
	// Load the simple vert and frag shaders into the m_simpleShader variable
	m_simpleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (!m_simpleShader.link())
	{
		printf("Simple Shader has an Error: %s\n", m_simpleShader.getLastError());
		return false;
	}

	// Defined as 4 vertices for the 2 triangles
	Mesh::Vertex vertices[4];

	vertices[0].position = {-0.5f, 0,  0.5f, 1};
	vertices[1].position = { 0.5f, 0,  0.5f, 1};
	vertices[2].position = {-0.5f, 0, -0.5f, 1};
	vertices[3].position = { 0.5f, 0, -0.5f, 1};

	unsigned int indices[6] = {0, 1, 2, 2, 1, 3};

	m_quadMesh.Initialise(4, vertices, 6, indices);
	
	// This is a 10 'unit' wide quad
	m_quadTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1
	};

	return true;
}

void GraphicsApp::QuadDraw(mat4 _pvm)
{
	// Bind the shader
	m_simpleShader.bind();

	// Bind the transform
	m_simpleShader.bindUniform("ProjectionViewModel", _pvm);

	// Draw the quad using the mesh's draw
	m_quadMesh.Draw();
}

bool GraphicsApp::BunnyLoader()
{
	m_colorShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/color.vert");
	m_colorShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/color.frag");

	// Check if the color shader has loaded successfully
	if (!m_colorShader.link())
	{
		printf("Color Shader Error: %s\n", m_colorShader.getLastError());
		return false;
	}

	// Check if bunny mesh has loaded successfully
	if (!m_bunnyMesh.load("./stanford/Bunny.obj"))
	{
		printf("Bunny Mesh Error:\n");
		return false;
	}

	m_bunnyTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return true;
}

void GraphicsApp::BunnyDraw(mat4 _pvm)
{
	// Bind the shader
	m_colorShader.bind();

	// Bind the transform
	m_colorShader.bindUniform("ProjectionViewModel", _pvm);

	// Bind the color
	m_colorShader.bindUniform("BaseColor", vec4(1, 0, 0, 0.5f));

	// Draw the obj using the mesh's draw
	m_bunnyMesh.draw();
}
