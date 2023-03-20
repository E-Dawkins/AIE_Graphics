#pragma once
#include "Application.h"

#include <glm/glm.hpp>

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
	
	struct Light
	{
		glm::vec3 direction;
		glm::vec3 color;
	};

protected:
	Scene* m_scene = nullptr;
};
