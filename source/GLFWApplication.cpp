#include "GLFWApplication.h"
#include "ApplicationEventListener.h"
#include "ApplicationUpdateListener.h"
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

GLFWApplication::GLFWApplication(const ApplicationSettings& settings) 
	: _window(nullptr)
	, _settings(settings)
	, mRunning(true)
{

}

GLFWApplication::~GLFWApplication() {
	destroy();
}

void GLFWApplication::registerEventListener(IApplicationEventListener* listener) {
	_eventListeners.push_back(listener);
}

void GLFWApplication::unregisterEventListener(IApplicationEventListener* listener) {
	for (int i = _eventListeners.size() - 1; i >= 0; --i) {
		if (_eventListeners[i] == listener) {
			_eventListeners.erase(_eventListeners.begin() + i);
		}
	}
}

void GLFWApplication::registerUpdateListener(IApplicationUpdateListener* listener) {
	_updateListeners.push_back(listener);
}

void GLFWApplication::unregisterUpdateListener(IApplicationUpdateListener* listener) {
	for (int i = _updateListeners.size() - 1; i >= 0; --i) {
		if (_updateListeners[i] == listener) {
			_updateListeners.erase(_updateListeners.begin() + i);
		}
	}
}

bool GLFWApplication::create() {
	if (_window) {
		destroy();
	}

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(_settings.videoMode.width, _settings.videoMode.height, "Simple example", nullptr, nullptr);
	if (!_window) {
		destroy();
		return false;
	}

	int majorVersion = glfwGetWindowAttrib(_window, GLFW_CONTEXT_VERSION_MAJOR);
	if (majorVersion < 3) {
		destroy();
		return false;
	}

	glfwSetFramebufferSizeCallback(_window, GLFWApplication::onWindowResize);
	glfwSetWindowCloseCallback(_window, GLFWApplication::onWindowReuqestClose);

	glfwSetWindowUserPointer(_window, this);
	glfwMakeContextCurrent(_window);

	sendCreatedEvent();

	glfwShowWindow(_window);
	
	return true;
}

void GLFWApplication::destroy() {	
	if (_window) {
		glfwDestroyWindow(_window);
		_window = nullptr;
	}	
	glfwTerminate();
}

void GLFWApplication::run() {
	if (!create()) {
		return;
	}

	while (mRunning) {
		sendUpdateEvent();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void GLFWApplication::close() {
	mRunning = false;
}

void GLFWApplication::sendUpdateEvent() {
	for (int i = _updateListeners.size() - 1; i >= 0; --i) {
		_updateListeners[i]->onApplicationUpdate();
	}
}

void GLFWApplication::sendResizeEvent(int width, int height) {
	ApplicationEvent appEvent;
	appEvent.type = ApplicationEvent::Resized;
	appEvent.size.width = width;
	appEvent.size.height = height;

	for (int i = _eventListeners.size() - 1; i >= 0; --i) {
		_eventListeners[i]->onApplicationEvent(appEvent);
	}
}

void GLFWApplication::sendCloseEvent() {
	ApplicationEvent appEvent;
	appEvent.type = ApplicationEvent::Closed;

	for (int i = _eventListeners.size() - 1; i >= 0; --i) {
		_eventListeners[i]->onApplicationEvent(appEvent);
	}
}

void GLFWApplication::sendCreatedEvent() {	
	ApplicationEvent appEvent;
	appEvent.type = ApplicationEvent::Created;

	for (int i = _eventListeners.size() - 1; i >= 0; --i) {
		_eventListeners[i]->onApplicationEvent(appEvent);
	}
}

void GLFWApplication::onWindowResize(GLFWwindow* window, int width, int height) {
	GLFWApplication* app = reinterpret_cast<GLFWApplication*>(glfwGetWindowUserPointer(window));
	if (app != nullptr) {
		app->sendResizeEvent(width, height);
	}
}

void GLFWApplication::onWindowReuqestClose(GLFWwindow* window) {
	GLFWApplication* app = reinterpret_cast<GLFWApplication*>(glfwGetWindowUserPointer(window));
	if (app != nullptr) {
		app->sendCloseEvent();
	}
}