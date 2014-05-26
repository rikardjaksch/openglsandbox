#include "GLFWApplication.h"
#include "OpenGLSandbox.h"

struct ShaderInfo {
	enum Type {
		Vertex,
		Fragment
	};	

	Type type;
	const char* filename;
	int _handle;
};

int main(int argc, char** argv) {
	ApplicationSettings settings;

	settings.videoMode.width = 1024;
	settings.videoMode.height = 768;
	settings.videoMode.fullscreen = false;

	GLFWApplication* app = new GLFWApplication(settings);
	OpenGLSandbox* sandbox = new OpenGLSandbox(app);
	
	app->run();

	ShaderInfo shaders[] = {
		{ShaderInfo::Vertex, "basic.vert"},
		{ShaderInfo::Fragment, "basic.frag"},
	};
	
	delete sandbox;
	delete app;

	return 0;
}