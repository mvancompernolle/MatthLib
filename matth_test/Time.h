#pragma once

class Time {
	bool initialized;
	Time() : initialized( false ) {}

	float mouseX, mouseY;
public:
	static Time& instance() { static Time instance; return instance; }

	bool initialize();
	bool update();
	bool terminate();
	bool isInitialized();

	float getTotalTime();
	float getDeltaTime();
};
#pragma once
