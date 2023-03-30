#pragma once
#include "Application.h"
#include "Mesh.h"

#include "OBJMesh.h"
#include "Shader.h"
#include "FlyCamera.h"
#include "Scene.h"
#include "ParticleEmitter.h"
#include "RenderTarget.h"

using glm::mat4;
using glm::vec3;

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
	ObjModel* LoadObjModel(char* _shaderName, char* _objFilePath, bool _flipTextures);

	bool LoadParticleSystem();
	void ParticleSystemDraw();
	
protected:
	FlyCamera			m_camera;
	
	int						m_sceneIndex = 0;
	std::vector<Scene*>		m_scenes;

	std::vector<ObjModel>	m_models;
	
	aie::RenderTarget		m_renderTarget;

	ParticleEmitter*		m_emitter;
	aie::ShaderProgram		m_particleShader;
	mat4					m_particleEmitTransform;
};
