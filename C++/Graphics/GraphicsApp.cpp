#include "GraphicsApp.h"

#include <imgui.h>

#include "Gizmos.h"
#include "Input.h"

#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Pyramid.h"
#include "Quad.h"
#include "Sphere.h"

#include "MeshInstance.h"
#include "ObjMeshInstance.h"
#include "StationaryCamera.h"

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
	
	delete m_emitter;
}

void GraphicsApp::update(float deltaTime)
{
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	GetActiveScene()->GetCamera()->Update(deltaTime);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();
	
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	// figure 8 for first point light in scene
	std::vector<Light>& pLights = GetActiveScene()->GetPointLights();

	if (!pLights.empty())
	{
		vec3 oldPos = pLights[0].direction;

		float newX = cos(getTime());
		float newZ = sin(2.f * getTime());

		pLights[0].direction = vec3(newX, oldPos.y, newZ);
	}
		
	m_emitter->Update(deltaTime, GetActiveScene()->GetCamera()->GetTransform());

	ImGuiRefresher();
}

void GraphicsApp::draw()
{
	// Bind the render target to result of last frame draw, then clear screen
	m_renderTarget.bind();
	clearScreen();

	// Main render ('draw') loop
	ParticleSystemDraw();
	GetActiveScene()->Draw();
	Gizmos::draw(GetActiveScene()->GetCamera()->GetProjectionViewMatrix());

	// Unbind the target to return to the backbuffer, then re-clear the screen
	m_renderTarget.unbind();
	clearScreen();

	// Apply post processing to result of THIS frames' draw
	GetActiveScene()->GetCamera()->PostProcessDraw(m_renderTarget);
}

bool GraphicsApp::LaunchScenes()
{
	if (!LoadParticleSystem())
		return false;
	
	if (!m_renderTarget.initialise(1, getWindowWidth(), getWindowHeight(), true))
		return false;
	
	if (!LoadModelScene())
		return false;
	
	if (!LoadPrimitiveScene())
		return false;

	return true;
}

bool GraphicsApp::LoadModelScene()
{
	// Create new scene with global / ambient light
	Light light = Light(vec3(1, -1, 1), vec3(1), 1.f);
	vec3 ambientLight = vec3(0.5f);

	// Create camera/s for scene
	FlyCamera* mainCam = new FlyCamera(vec3(0, 1, -3));
	StationaryCamera* statCam1 = new StationaryCamera(vec3(0, 1, 3),
										vec3(0, glm::pi<float>(), 0));
	
	// Create scene
	m_scenes.push_back(new Scene("Models", mainCam,
		vec2(getWindowWidth(), getWindowHeight()), light, ambientLight));

	// Set ImGui function delegate
	m_scenes.back()->SetImGuiFunction([this] { ImGuiModels(); });

	// Add camera/s to scene
	m_scenes.back()->AddCamera(statCam1);

	// Add point lights, at position with color and intensity
	m_scenes.back()->AddPointLight(vec3( 1, 2, 0), vec3(0, 1, 0), 1);
	m_scenes.back()->AddPointLight(vec3( 1, 1, 0), vec3(1, 0, 0), 10);
	m_scenes.back()->AddPointLight(vec3(-1, 1, 0), vec3(0, 0, 1), 10);

	// Load models
	ObjModel* trooper = LoadObjModel("normalLit", "./stormtrooper/stormtrooper.obj", true);
	ObjModel* spear = LoadObjModel("normalLit", "./soulspear/soulspear.obj", true);
	ObjModel* dragon = LoadObjModel("phong", "./stanford/dragon.obj", true);
	
	// Add models to scene
	m_scenes.back()->AddInstance(new ObjMeshInstance(vec3(0), vec3(0, 180.f, 0),
		vec3(0.5f), trooper->mesh, trooper->shader));
	m_scenes.back()->AddInstance(new ObjMeshInstance(vec3(2, 0.25f, 0), vec3(0), vec3(0.15f),
		spear->mesh, spear->shader));
	m_scenes.back()->AddInstance(new ObjMeshInstance(vec3(-2, 0.6f, 0), vec3(0), vec3(0.05f),
		dragon->mesh, dragon->shader));

	return true;
}

bool GraphicsApp::LoadPrimitiveScene()
{
	// Create new scene with global / ambient light
	Light light = Light(vec3(1, -1, 1), vec3(1), 1.f);
	vec3 ambientLight = vec3(0.5f);

	// Create camera/s for scene
	FlyCamera* mainCam = new FlyCamera(vec3(4, 1.5f, 0), vec3(0, glm::pi<float>() / 2.f, 0));
	
	// Create scene
	m_scenes.push_back(new Scene("Primitives", mainCam,
		vec2(getWindowWidth(), getWindowHeight()), light, ambientLight));

	// Set ImGui delegate
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
	m_scenes.back()->AddInstance(new MeshInstance(vec3(0), vec3(0),
		vec3(1), *quad, *colorShader, vec4(1, 0, 1, 1)));
	m_scenes.back()->AddInstance(new MeshInstance(vec3(0, -1, 0), vec3(0),
		vec3(1), *plane, *colorShader));
	m_scenes.back()->AddInstance(new MeshInstance(vec3(0, 1, 0), vec3(0),
		vec3(1), *cube, *colorShader, vec4(1, 0, 0, 1)));
	m_scenes.back()->AddInstance(new MeshInstance(vec3(-2, 1, 0), vec3(0),
		vec3(1), *pyramid, *colorShader, vec4(0, 1, 0, 1)));
	m_scenes.back()->AddInstance(new MeshInstance(vec3(2, 1, 0), vec3(0),
		vec3(1), *sphere, *colorShader, vec4(0, 0, 1, 1)));
	m_scenes.back()->AddInstance(new MeshInstance(vec3(0, 1, -2), vec3(0),
		vec3(1), *cone, *colorShader, vec4(1, 1, 0, 1)));
	m_scenes.back()->AddInstance(new MeshInstance(vec3(0, 1, 2), vec3(0),
		vec3(1), *cylinder, *colorShader, vec4(0, 1, 1, 1)));
	
	return true;
}

void GraphicsApp::ImGuiRefresher()
{
	/* --- Scene Select --- */
	
	ImGui::Begin("Scene Select");

	std::vector<const char*> items;

	for (auto scene : m_scenes)
		items.push_back(scene->GetSceneName());
	
	ImGui::ListBox("", &m_sceneIndex, items.data(), (int)items.size());
	
	ImGui::End();

	/* --- Scene ImGui --- */
	
	GetActiveScene()->ImGuiRefresher();
}

void GraphicsApp::ImGuiModels()
{
	ImGui::Begin("Light Settings");

	ImGui::ColorEdit4("Global Light Color", &GetActiveScene()->GetSunLight().color[0], false);
	ImGui::ColorEdit4("Ambient Light Color", &GetActiveScene()->GetAmbientLightColor()[0], false);

	std::vector<Light>& pointLights = GetActiveScene()->GetPointLights();
	
	for (int i = 0; i < pointLights.size(); i++)
	{
		std::string iString = std::to_string(i);

		if (ImGui::CollapsingHeader(("Point Light " + iString).c_str()))
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

ObjModel* GraphicsApp::LoadObjModel(char* _shaderName, char* _objFilePath, bool _flipTextures)
{
	ObjModel* model = new ObjModel();

	// Load model shader
	if (!LoadShader(_shaderName, model->shader))
	{
		printf("Shader Error!\n%s", model->shader.getLastError());
		return nullptr;
	}

	// Check if mesh has loaded successfully
	if (!model->mesh.load(_objFilePath, true, _flipTextures))
	{
		printf("Mesh Error! Could not load:\n\t%s", _objFilePath);
		return nullptr;
	}
	
	return model;
}

bool GraphicsApp::LoadParticleSystem()
{
	if (!LoadShader("particle", m_particleShader))
		return false;

	m_emitter = new ParticleEmitter();
	m_emitter->Initialise(1000, 500, .1f, 1.f, .1f, 1,
		0.5f, .05f, vec4(1, 0, 0, 1), vec4(1, 0.5, 0, 1));

	m_emitter->SetGravity(true, vec3(0, -0.1f, 0));
	
	m_particleEmitTransform = mat4(1);

	return true;
}

void GraphicsApp::ParticleSystemDraw()
{
	m_particleEmitTransform = translate(m_particleEmitTransform,
		vec3(cos(getTime()), 0, 0) * 0.1f);

	m_emitter->UpdatePosition(m_particleEmitTransform[3]);

	auto pv = GetActiveScene()->GetCamera()->GetProjectionViewMatrix();
	
	m_particleShader.bind();
	m_particleShader.bindUniform("ProjectionViewModel",
		pv * m_particleEmitTransform);
	m_emitter->Draw();
}