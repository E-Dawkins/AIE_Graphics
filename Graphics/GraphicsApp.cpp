#include "GraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "BunnyScene.h"
#include "PrimitiveScene.h"
#include "SolarSystem.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

GraphicsApp* GraphicsApp::instance = nullptr;

bool GraphicsApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	viewMatrix = lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.f / 9.f, 0.1f, 1000.f);
	
	m_scene = new PrimitiveScene();
	m_scene->Start();
	
	return true;
}

void GraphicsApp::shutdown() {

	Gizmos::destroy();
}

void GraphicsApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	m_scene->Update(deltaTime);
	m_scene->ImGuiRefresher();

	m_camera.Update(deltaTime);
	
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GraphicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	viewMatrix = m_camera.GetViewMatrix();
	projectionMatrix = m_camera.GetProjectionMatrix(getWindowWidth(), (float)getWindowHeight());
	
	pvMatrix = projectionMatrix * viewMatrix;
	
	m_scene->Draw();
	
	Gizmos::draw(pvMatrix);
}