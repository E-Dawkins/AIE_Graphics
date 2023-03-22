#include "GraphicsApp.h"

#include <imgui.h>

#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Gizmos.h"
#include "Input.h"
#include "Plane.h"
#include "Pyramid.h"

#include "Quad.h"
#include "Sphere.h"

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
	ImGui::Begin("Scenes");

	std::vector<const char*> items;

	for (auto scene : m_scenes)
		items.push_back(scene->GetSceneName());
	
	ImGui::ListBox("Current Scene", &m_sceneIndex, items.data(), (int)items.size());
	
	ImGui::End();
	
	
	ImGui::Begin("Light Settings");

	ImGui::ColorEdit4("Global Light Color", &m_scenes[m_sceneIndex]->GetLight().color[0], false);
	ImGui::ColorEdit4("Ambient Light Color", &m_scenes[m_sceneIndex]->GetAmbientLightColor()[0], false);
	
	ImGui::End();
}

bool GraphicsApp::LaunchScenes()
{
	if (!LoadRobotScene())
		return false;

	if (!LoadPrimitiveScene())
		return false;

	return true;
}

bool GraphicsApp::LoadRobotScene()
{
	// Create new scene with a simple fly camera,
	// and global light / ambient light
	m_camera = SimpleCamera();
	m_camera.SetPosition(vec3(0, 0.75f, -3));
	
	Light light = Light(vec3(1, -1, 1), vec3(1), 1.f);
	vec3 ambientLight = vec3(0.5f);
	
	m_scenes.push_back(new Scene("Robot", m_camera, vec2(getWindowWidth(),
		getWindowHeight()), light, ambientLight));

	// Add point lights, at position with color and intensity
	m_scenes.back()->AddPointLights(vec3(5, 3, 0), vec3(1, 0, 0), 50);
	m_scenes.back()->AddPointLights(vec3(-5, 3, 0), vec3(0, 0, 1), 50);

	// If shader or object does not load, scene loading returns false
	if (!LoadShader("normalLit", m_robotShader) || !LoadObj("./robot/robot.obj", m_robotMesh, true))
		return false;

	// Create a line of robots, with a slight rotation applied
	int maxRobots = 10;
	for (int i = 0; i < maxRobots; i++)
	{
		m_scenes.back()->AddInstance(new Instance(vec3(-maxRobots + i * 2, 0, 0),
			vec3(0, i * 30, 0), vec3(0.1f), m_robotMesh, m_robotShader));
	}

	return true;
}

bool GraphicsApp::LoadPrimitiveScene()
{
	// Create new scene with a simple fly camera,
	// and global light / ambient light
	m_camera = SimpleCamera();
	m_camera.SetPosition(vec3(2, 1, -2));

	Light light = Light(vec3(1, -1, 1), vec3(1), 1.f);
	vec3 ambientLight = vec3(0.5f);
	
	m_scenes.push_back(new Scene("Primitives", m_camera, vec2(getWindowWidth(),
		getWindowHeight()), light, ambientLight));

	// Load color shader
	aie::ShaderProgram* colorShader = new aie::ShaderProgram();
	if (!LoadShader("color", *colorShader))
		return false;
	
	// Make all primitives
	Quad* quad = new Quad();
	Plane* plane = new Plane(10, 10);
	Cube* cube = new Cube();
	Pyramid* pyramid = new Pyramid();
	Sphere* sphere = new Sphere(10, 10);
	Cone* cone = new Cone(10);
	Cylinder* cylinder = new Cylinder(10);

	// Add all primitives to scene
	m_scenes.back()->AddInstance(new Instance(vec3(0), vec3(0),
		vec3(1), *quad, *colorShader, vec4(1, 0, 1, 1)));
	m_scenes.back()->AddInstance(new Instance(vec3(0, -1, 0), vec3(0),
		vec3(1), *plane, *colorShader));
	m_scenes.back()->AddInstance(new Instance(vec3(0, 1, 0), vec3(0),
		vec3(1), *cube, *colorShader, vec4(1, 0, 0, 1)));
	m_scenes.back()->AddInstance(new Instance(vec3(-2, 1, 0), vec3(0),
		vec3(1), *pyramid, *colorShader, vec4(0, 1, 0, 1)));
	m_scenes.back()->AddInstance(new Instance(vec3(2, 1, 0), vec3(0),
		vec3(1), *sphere, *colorShader, vec4(0, 0, 1, 1)));
	m_scenes.back()->AddInstance(new Instance(vec3(0, 1, -2), vec3(0),
		vec3(1), *cone, *colorShader, vec4(1, 1, 0, 1)));
	m_scenes.back()->AddInstance(new Instance(vec3(0, 1, 2), vec3(0),
		vec3(1), *cylinder, *colorShader, vec4(0, 1, 1, 1)));
	
	return true;
}

bool GraphicsApp::LoadObj(const char* _filePath, aie::OBJMesh& _mesh, bool _flipTexture)
{
	// Check if mesh has loaded successfully
	if (!_mesh.load(_filePath, true, _flipTexture))
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