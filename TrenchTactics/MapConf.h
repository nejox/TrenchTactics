#pragma once
class MapConf {
private:
	int seed;
	int sizeX;
	int sizeY;
public:
	int getSeed() {
		return this->seed;
	}
	int getSizeX() {
		return this->sizeX;
	}
	int getSizeY() {
		return this->sizeY;
	}
};