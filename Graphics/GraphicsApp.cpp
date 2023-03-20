#include "GraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"

#include "BunnyScene.h"
#include "PrimitiveScene.h"
#include "SolarSystem.h"

using aie::Gizmos;

GraphicsApp* GraphicsApp::instance = nullptr;

bool GraphicsApp::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);
	
	m_scene = new BunnyScene();
	m_scene->Start();
	
	return true;
}

void GraphicsApp::shutdown()
{
	Gizmos::destroy();
}

void GraphicsApp::update(float deltaTime)
{
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	m_scene->Update(deltaTime);
	m_scene->ImGuiRefresher();
	
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GraphicsApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();
	
	m_scene->Draw();
}