#pragma once

#include <vector>
#include "ApplicationSettings.h"

struct GLFWwindow;
class IApplicationEventListener;
class IApplicationUpdateListener;

class GLFWApplication {
public:
	GLFWApplication(const ApplicationSettings& settings);
	~GLFWApplication();

	void registerEventListener(IApplicationEventListener* listener);
	void unregisterEventListener(IApplicationEventListener* listener);
	void registerUpdateListener(IApplicationUpdateListener* listener);
	void unregisterUpdateListener(IApplicationUpdateListener* listener);
		
	void run();
	void close();

protected:
	bool create();
	void destroy();

	void sendUpdateEvent();
	void sendResizeEvent(int width, int height);
	void sendCloseEvent();
	void sendCreatedEvent();
	
	static void onWindowResize(GLFWwindow* window, int width, int height);
	static void onWindowReuqestClose(GLFWwindow* window);

private:
	GLFWwindow*	_window;
	ApplicationSettings _settings;
	bool mRunning;
	std::vector<IApplicationEventListener*> _eventListeners;
	std::vector<IApplicationUpdateListener*> _updateListeners;
};