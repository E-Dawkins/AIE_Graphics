#pragma once
#include "Application.h"

#include <glm/glm.hpp>

#include "OBJMesh.h"
#include "Shader.h"
#include "SimpleCamera.h"
#include "Scene.h"
#include "Instance.h"
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
	bool LoadTrooperScene();
	bool LoadPrimitiveScene();
	
	void ImGuiRefresher();
	void ImGuiTroopers();
	void ImGuiPrimitive();
	
	bool LoadObj(const char* _filePath, aie::OBJMesh& _mesh, bool _flipTexture);
	bool LoadShader(const char *_fileName, aie::ShaderProgram& _shader);

	bool LoadQuad();
	void DrawQuad();

protected:
	SimpleCamera m_camera;

	aie::RenderTarget m_renderTarget;

	int m_sceneIndex = 0;
	std::vector<Scene*> m_scenes;

	std::vector<ObjModel> m_models;

	// Post-Processing
	aie::ShaderProgram m_quadShader;
	Mesh m_quadMesh;
	mat4 m_quadTransform;
};
