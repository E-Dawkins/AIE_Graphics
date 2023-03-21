#include "GraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"

#include "BunnyScene.h"
#include "Instance.h"
#include "PrimitiveScene.h"
#include "SolarSystem.h"

using aie::Gizmos;

GraphicsApp* GraphicsApp::instance = nullptr;

bool GraphicsApp::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	m_camera = new SimpleCamera();
	m_camera->SetPosition(vec3(0, 0.75f, -3));
	
	Light light = Light(vec3(1, 1, 1), vec3(1), 1.f);
	m_ambientLight = vec3(0.5f);
	
	m_scene = new Scene(m_camera, vec2(getWindowWidth(), getWindowHeight()),
		light, m_ambientLight);

	LoadObj("./robot/robot.obj", m_robotMesh);
	LoadShader("normalLit", m_robotShader);
	m_robotTransform = rotate(mat4(1), glm::pi<float>(), vec3(0, 1, 0));
	m_robotTransform = scale(m_robotTransform, vec3(0.1f));
	
	m_scene->AddInstance(new Instance(m_robotTransform, &m_robotMesh, &m_robotShader));
	
	return true;
}

void GraphicsApp::shutdown()
{
	Gizmos::destroy();
	delete m_scene;
}

void GraphicsApp::update(float deltaTime)
{
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();
	
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GraphicsApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	m_scene->GetLight().direction = vec3(glm::cos(getTime()), glm::sin(getTime()), 0);
	m_scene->Draw();
}

void GraphicsApp::LoadObj(char* _filePath, aie::OBJMesh& _mesh)
{
	// Check if bunny mesh has loaded successfully
	if (!_mesh.load(_filePath, true, true))
	{
		printf("Mesh Error! Could not load:\n\t%s", _filePath);
		return;
	}
}

void GraphicsApp::LoadShader(char* _fileName, aie::ShaderProgram& _shader)
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
		return;
	}
}
