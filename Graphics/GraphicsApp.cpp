#include "GraphicsApp.h"

#include <imgui.h>

#include "Gizmos.h"
#include "Input.h"

using aie::Gizmos;

GraphicsApp* GraphicsApp::instance = nullptr;

bool GraphicsApp::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);
	
	return LaunchScenes();
}

void GraphicsApp::shutdown()
{
	Gizmos::destroy();

	for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
	{
		delete* it;
	}
}

void GraphicsApp::update(float deltaTime)
{
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	m_camera.Update(deltaTime);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();
	
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	ImGuiRefresher();
}

void GraphicsApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	m_scenes[m_sceneIndex]->Draw();
}

void GraphicsApp::ImGuiRefresher()
{
	ImGui::Begin("Light Settings");

	ImGui::ColorEdit4("Global Light Color", &m_scenes[m_sceneIndex]->GetLight().color[0], false);
	ImGui::ColorEdit4("Ambient Light Color", &m_scenes[m_sceneIndex]->GetAmbientLightColor()[0], false);
	
	ImGui::End();
}

bool GraphicsApp::LaunchScenes()
{
	if (!LoadRobotScene(0))
		return false;

	return true;
}

bool GraphicsApp::LoadRobotScene(int _sceneIndex)
{
	// Create new scene with a simple fly camera,
	// and global light / ambient light
	m_camera = SimpleCamera();
	m_camera.SetPosition(vec3(0, 0.75f, -3));
	
	Light light = Light(vec3(1, -1, 1), vec3(1), 1.f);
	vec3 ambientLight = vec3(0.5f);
	
	m_scenes.push_back(new Scene(m_camera, vec2(getWindowWidth(),
		getWindowHeight()), light, ambientLight));

	// Add point lights, at position with color and intensity
	// m_scenes.back()->AddPointLights(vec3(5, 3, 0), vec3(1, 0, 0), 50);
	// m_scenes.back()->AddPointLights(vec3(-5, 3, 0), vec3(0, 0, 1), 50);

	// If shader or object does not load, scene loading returns false
	if (!LoadShader("normalLit", m_robotShader) || !LoadObj("./robot/robot.obj", m_robotMesh, true))
		return false;

	// Create a line of robots, with a slight rotation applied
	for (int i = 0; i < 10; i++)
	{
		m_scenes.back()->AddInstance(new Instance(vec3(i * 2, 0, 0), vec3(0, 180 + i * 30, 0),
							vec3(0.1f), m_robotMesh, m_robotShader));
	}

	return true;
}

bool GraphicsApp::LoadObj(const char* _filePath, aie::OBJMesh& _mesh, bool _flipTexture)
{
	// Check if mesh has loaded successfully
	if (!_mesh.load(_filePath, true, true))
	{
		printf("Mesh Error! Could not load:\n\t%s", _filePath);
		return false;
	}

	return true;
}

bool GraphicsApp::LoadShader(const char* _fileName, aie::ShaderProgram& _shader)
{
	std::string vertPath = "./shaders/";
	vertPath.append(_fileName);
    
	std::string fragPath = vertPath;

	vertPath.append(".vert");
	fragPath.append(".frag");
    
	// Load the simple vert and frag shaders into the m_simpleShader variable
	_shader.loadShader(aie::eShaderStage::VERTEX, vertPath.c_str());
	_shader.loadShader(aie::eShaderStage::FRAGMENT, fragPath.c_str());

	if (!_shader.link())
	{
		printf("Shader Error!\n\t%s", _shader.getLastError());
		return false;
	}

	return true;
}