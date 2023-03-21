#pragma once
#include "Application.h"

#include <glm/glm.hpp>

#include "OBJMesh.h"
#include "Shader.h"

class Scene;
class SimpleCamera;

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

	void LoadObj(char* _filePath, aie::OBJMesh& _mesh);
	void LoadShader(char *_fileName, aie::ShaderProgram& _shader);

protected:
	SimpleCamera* m_camera;
	glm::vec3 m_ambientLight;
	
	Scene* m_scene;

	aie::OBJMesh m_robotMesh;
	glm::mat4 m_robotTransform;
	aie::ShaderProgram m_robotShader;
};
