#include "Time.h"
#include "Window.h"
#include "sfwdraw.h"

bool Time::initialize() {
	return initialized = Window::instance().isInitialized();
}

bool Time::update() {
	return true;
}

bool Time::terminate() {
	return true;
}

bool Time::isInitialized() {
	return initialized;
}

float Time::getTotalTime() {
	return sfw::getTime();
}

float Time::getDeltaTime() {
	return sfw::getDeltaTime();
}