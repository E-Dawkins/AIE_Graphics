#pragma once

#include <vector>

#include "Application.h"
#include <glm/mat4x4.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "OBJMesh.h"

using glm::mat4;
class Scene;

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

	// camera transforms
	mat4 viewMatrix = mat4(1);
	mat4 projectionMatrix = mat4(1);
	mat4 pvMatrix = mat4(1);

protected:
	Scene* m_scene = nullptr;
};
