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

struct PostProcessEffect
{
	const char* name;
	int type;
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

	bool LoadPostProcessing();
	void PostProcessDraw();

	bool LoadParticleSystem();
	void ParticleSystemDraw();
	
protected:
	FlyCamera			m_camera;
	
	int						m_sceneIndex = 0;
	std::vector<Scene*>		m_scenes;

	std::vector<ObjModel>	m_models;
	
	std::vector<PostProcessEffect> m_effects =
	{
		{"Default",			-1},
		{"Box Blur",		0},
		{"Gaussian Blur",	1},
		{"Distort",			2},
		{"Edge Detection",	3},
		{"Sepia",			4},
		{"Scanlines",		5},
		{"Grayscale",		6},
		{"Invert",			7},
		{"Pixelization",	8},
		{"Posterization",	9},
		{"Distance Fog",	10},
		{"Depth of Field",	11},
		{"Vignette",		12}
	};
	
	aie::RenderTarget		m_renderTarget;
	aie::ShaderProgram		m_postProcessShader;
	Mesh					m_postProcessQuad;
	int						m_postProcessEffect = m_effects[0].type;

	ParticleEmitter*		m_emitter;
	aie::ShaderProgram		m_particleShader;
	mat4					m_particleEmitTransform;
};
