#include "GraphicsApp.h"

int main() {
	
	// allocation
	GraphicsApp* app;

	GraphicsApp::create();

	// initialise and loop
	GraphicsApp::instance->run("AIE", 1280, 720, false);

	GraphicsApp::destroy();

	return 0;
}