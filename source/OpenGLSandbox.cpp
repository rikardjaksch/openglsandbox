#include "OpenGLSandbox.h"
#include "GLFWApplication.h"
#include <iostream>

#include <glfw/glfw3.h>

OpenGLSandbox::OpenGLSandbox(GLFWApplication* app)
	: mApplication(app)
{
	mApplication->registerEventListener(this);
	mApplication->registerUpdateListener(this);
}

OpenGLSandbox::~OpenGLSandbox() {
	mApplication->unregisterUpdateListener(this);
	mApplication->unregisterEventListener(this);
}

void OpenGLSandbox::onApplicationEvent(const ApplicationEvent& appEvent) {
	if (appEvent.type == ApplicationEvent::Resized) {
		std::cout << "Window resized (" << appEvent.size.width << "x" << appEvent.size.height << ")" << std::endl;
	} else if (appEvent.type == ApplicationEvent::Closed) {
		std::cout << "Application shutdown..." << std::endl;
		shutdown();
		mApplication->close();
	} else if (appEvent.type == ApplicationEvent::Created) {
		std::cout << "Application initialized..." << std::endl;
		initialize();
	}
}

void OpenGLSandbox::onApplicationUpdate() {
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void OpenGLSandbox::initialize() {
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLSandbox::shutdown() {	
}