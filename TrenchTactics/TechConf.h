#pragma once

/**
 * Tech configuration data container with all getters and setters
 */
class TechConf {
private:
	int fps;
	int windowSizeX;
	int windowSizeY;
	std::string textFont;
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
	void setTextFont(std::string textFont) {
		this->textFont = textFont;
	}
	std::string getTextFont() {
		return this->textFont;
	}
};