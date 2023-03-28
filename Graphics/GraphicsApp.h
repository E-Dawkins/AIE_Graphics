#pragma once
#include "Application.h"

#include <glm/glm.hpp>

#include "OBJMesh.h"
#include "Shader.h"
#include "SimpleCamera.h"
#include "Scene.h"
#include "Instance.h"
#include "ParticleEmitter.h"
#include "RenderTarget.h"

struct ObjModel
{
	aie::OBJMesh mesh;
	aie::ShaderProgram shader;
};

class GraphicsApp : public aie::Application {
public:
	GraphicsApp() = default;
	virtual ~GraphicsApp() = default;
	
	static GraphicsApp* instance;

	static void create()			{ instance = new GraphicsApp(); }
	static void destroy()			{ delete instance; }
	
	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	bool LaunchScenes();
	bool LoadModelScene();
	bool LoadPrimitiveScene();

	Scene* GetActiveScene() { return m_scenes[m_sceneIndex]; }
	
	void ImGuiRefresher();
	void ImGuiModels();
	void ImGuiPrimitive();
	
	static bool LoadObj(const char* _filePath, aie::OBJMesh& _mesh, bool _flipTexture);
	static bool LoadShader(const char *_fileName, aie::ShaderProgram& _shader);

	bool LoadPostProcessing();
	void PostProcessDraw();

	bool LoadParticleSystem();
	void ParticleSystemDraw();

	ObjModel* LoadObjModel(char* _shaderName, char* _objFilePath, bool _flipTextures);
	
protected:
	SimpleCamera			m_camera;

	aie::RenderTarget		m_renderTarget;

	int						m_sceneIndex = 0;
	std::vector<Scene*>		m_scenes;

	std::vector<ObjModel>	m_models;
	
	aie::ShaderProgram		m_postProcessShader;
	Mesh					m_postProcessQuad;
	int						m_postProcessEffect = -1;

	ParticleEmitter*		m_emitter;
	aie::ShaderProgram		m_particleShader;
	mat4					m_particleEmitTransform;
};
