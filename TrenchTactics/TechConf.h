#pragma once

class TechConf {
private:
	int fps;
	int windowSizeX;
	int windowSizeY;
public:
	int getFPS() {
		return this->fps;
	}
	int getWindowsSizeX() {
		return this->windowSizeX;
	}
	int getWindowsSizeY() {
		return this->windowSizeY;
	}
};