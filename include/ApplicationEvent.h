#pragma once

class ApplicationEvent {
public:
	struct SizeEvent {
		int width;
		int height;
	};

	enum EventType {
		Resized,
		LostFocus,
		GainedFocus,
		Minimized,
		Restored,
		Created,
		Closed
	};

	EventType type;
	union {
		SizeEvent size;
	};
};

