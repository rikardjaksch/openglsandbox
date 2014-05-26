#pragma once

#include "ApplicationEvent.h"

class IApplicationEventListener {
public:
	virtual void onApplicationEvent(const ApplicationEvent& appEvent) = 0;
};

