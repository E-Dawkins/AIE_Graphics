#include "GraphicsApp.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

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
	// Bind the render target as the first part of our draw function
	m_renderTarget.bind();
	
	// wipe the screen to the background colour
	clearScreen();

	m_scenes[m_sceneIndex]->Draw();

	// // Unbind the target to return to the backbuffer
	m_renderTarget.unbind();
	clearScreen();

	DrawQuad();
}

bool GraphicsApp::LaunchScenes()
{
	if (!m_renderTarget.initialise(1, getWindowWidth(), getWindowHeight()))
		return false;

	if (!LoadQuad())
		return false;
	
	if (!LoadTrooperScene())
		return false;
	
	if (!LoadPrimitiveScene())
		return false;

	return true;
}

bool GraphicsApp::LoadTrooperScene()
{
	// Create new scene with a simple fly camera,
	// and global light / ambient light
	m_camera = SimpleCamera();
	m_camera.SetPosition(vec3(0, 0.75f, -3));
	
	Light light = Light(vec3(1, -1, 1), vec3(1), 1.f);
	vec3 ambientLight = vec3(0.5f);
	
	m_scenes.push_back(new Scene("Models", m_camera, vec2(getWindowWidth(),
		getWindowHeight()), light, ambientLight));

	m_scenes.back()->SetImGuiFunction([this] { ImGuiTroopers(); });

	// Add point lights, at position with color and intensity
	m_scenes.back()->AddPointLights(vec3(5, 3, 0), vec3(1, 0, 0), 50);
	m_scenes.back()->AddPointLights(vec3(-5, 3, 0), vec3(0, 0, 1), 50);

	m_models.push_back(ObjModel());
	
	// If shader or object does not load, scene loading returns false
	if (!LoadShader("normalLit", m_models[0].shader) || !LoadObj("./stormtrooper/stormtrooper.obj", m_models[0].mesh, true))
		return false;

	m_scenes.back()->AddInstance(new Instance(vec3(2, 0.5f, 0),
			vec3(0, 180.f, 0), vec3(0.25f), m_models[0].mesh, m_models[0].shader));

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

	m_scenes.back()->SetImGuiFunction([this] { ImGuiPrimitive(); });

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

void GraphicsApp::ImGuiRefresher()
{
	ImGui::Begin("Scene Select");

	std::vector<const char*> items;

	for (auto scene : m_scenes)
		items.push_back(scene->GetSceneName());
	
	ImGui::ListBox("", &m_sceneIndex, items.data(), (int)items.size());
	
	ImGui::End();

	ImGui::Begin("Camera Settings");

	float tempSens = glm::degrees(m_camera.GetSensitivity());
	ImGui::DragFloat("Sensitivity", &tempSens, 1.f, 5.f, 180.f);
	m_camera.SetSensitivity(glm::radians(tempSens));
	
	ImGui::End();

	m_scenes[m_sceneIndex]->ImGuiRefresher();
}

void GraphicsApp::ImGuiTroopers()
{
	ImGui::Begin("Light Settings");

	ImGui::ColorEdit4("Global Light Color", &m_scenes[m_sceneIndex]->GetLight().color[0], false);
	ImGui::ColorEdit4("Ambient Light Color", &m_scenes[m_sceneIndex]->GetAmbientLightColor()[0], false);

	std::vector<Light>& pointLights = m_scenes[m_sceneIndex]->GetPointLights();
	
	for (int i = 0; i < pointLights.size(); i++)
	{
		std::string iString = std::to_string(i);

		if (ImGui::CollapsingHeader(("Point Light : " + iString).c_str()))
		{
			Light& light = pointLights[i];

			vec3 color = light.color / light.intensity;
			
			ImGui::ColorEdit3((iString + " : Color").c_str(), &color[0]);
			ImGui::DragFloat((iString + " : Intensity").c_str(), &light.intensity, 0.5f, 1.f, 100.f);
			ImGui::DragFloat3((iString + " : Position").c_str(), &light.direction[0], 0.1f);
			
			light.color = color * light.intensity;
		}
	}
	
	ImGui::End();
}

void GraphicsApp::ImGuiPrimitive()
{
	
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

bool GraphicsApp::LoadQuad()
{
	// Load the simple vert and frag shaders into the m_simpleShader variable
	m_quadShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_quadShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");

	if (!m_quadShader.link())
	{
		printf("Quad Shader has an Error: %s\n", m_quadShader.getLastError());
		return false;
	}

	m_quadMesh.InitialiseQuad();

	m_quadTransform = scale(mat4(1), vec3(10));
	
	return true;
}

void GraphicsApp::DrawQuad()
{
	mat4 pvm = m_camera.GetProjectionViewMatrix() * m_quadTransform;
	
	m_quadShader.bind();

	m_quadShader.bindUniform("ProjectionViewModel", pvm);

	m_quadShader.bindUniform("diffuseTexture", 0);

	m_renderTarget.getTarget(0).bind(0);

	m_quadMesh.Draw();
}
