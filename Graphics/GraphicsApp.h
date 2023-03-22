#pragma once
#include "Application.h"

#include <glm/glm.hpp>

#include "OBJMesh.h"
#include "Shader.h"
#include "SimpleCamera.h"
#include "Scene.h"
#include "Instance.h"

// Primitives
class Quad;

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

	void ImGuiRefresher();

	bool LaunchScenes();
	bool LoadRobotScene();
	bool LoadPrimitiveScene();
	
	bool LoadObj(const char* _filePath, aie::OBJMesh& _mesh, bool _flipTexture);
	bool LoadShader(const char *_fileName, aie::ShaderProgram& _shader);

protected:
	SimpleCamera m_camera;

	int m_sceneIndex = 0;
	std::vector<Scene*> m_scenes;

	aie::OBJMesh m_robotMesh;
	aie::ShaderProgram m_robotShader;
};
