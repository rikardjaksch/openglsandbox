#pragma once

#include "ApplicationEventListener.h"
#include "ApplicationUpdateListener.h"

class GLFWApplication;

class OpenGLSandbox : public IApplicationEventListener, public IApplicationUpdateListener {
public:
	OpenGLSandbox(GLFWApplication* app);
	~OpenGLSandbox();

	void onApplicationEvent(const ApplicationEvent& appEvent);
	void onApplicationUpdate();

protected:
	void initialize();
	void shutdown();

private:
	GLFWApplication*	mApplication;
};