#pragma once

class ApplicationSettings {
public:
	struct VideoModeSettings {
		VideoModeSettings()
			: width(1024)
			, height(768)
			, fullscreen(false)
		{}

		int width;
		int height;
		bool fullscreen;
	};

	VideoModeSettings videoMode;
};

