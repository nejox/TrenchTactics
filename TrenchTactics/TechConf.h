#pragma once

/// <summary>
/// Tech configeration data container with all getters and setters
/// </summary>
class TechConf {
private:
	int fps;
	int windowSizeX;
	int windowSizeY;
public:
	void setFPS(int fps) {
		this->fps = fps;
	}
	int getFPS() {
		return this->fps;
	}
	void setWindowSizeX(int windowSizeX) {
		this->windowSizeX = windowSizeX;
	}
	int getWindowSizeX() {
		return this->windowSizeX;
	}
	void setWindowSizeY(int windowSizeY) {
		this->windowSizeY = windowSizeY;
	}
	int getWindowSizeY() {
		return this->windowSizeY;
	}
};