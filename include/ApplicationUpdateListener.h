#pragma once

class IApplicationUpdateListener {
public:
	virtual ~IApplicationUpdateListener() {}
	virtual void onApplicationUpdate() = 0;
};