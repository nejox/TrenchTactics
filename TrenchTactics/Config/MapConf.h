#pragma once

/// <summary>
/// Map configeration data container with all getters and setters
/// </summary>
class MapConf {
private:
	int seed;
	int sizeX;
	int sizeY;
public:
	void setSeed(int seed) {
		this->seed = seed;
	}
	int getSeed() {
		return this->seed;
	}
	void setSizeX(int sizeX) {
		this->sizeX = sizeX;
	}
	int getSizeX() {
		return this->sizeX;
	}
	void setSizeY(int sizeY) {
		this->sizeY = sizeY;
	}
	int getSizeY() {
		return this->sizeY;
	}
};