#include "Input.h"
#include "Window.h"
#include "sfwdraw.h"
#include "Time.h"
#include <cstring>
#include <iostream>

bool Input::initialize() {
	memset( keyRelease, 0, 400 );
	memset( keyPress, 0, 400 );
	memset( mouseRelease, 0, 10 );
	memset( mousePress, 0, 10 );
	return initialized = Window::instance().isInitialized();
}

bool Input::update() {
	for ( unsigned i = 0; i < 400; ++i ) {
		keyState[i] = keyPress[i] > keyRelease[i];
		if ( sfw::getKey( i ) ) {
			keyPress[i] = Time::instance().getTotalTime();
		}
		else {
			keyRelease[i] = Time::instance().getTotalTime();
		}
	}

	for ( unsigned i = 0; i < 10; ++i ) {
		mouseState[i] = mousePress[i] > mouseRelease[i];
		if ( sfw::getMouseButton( i ) ) {
			mousePress[i] = Time::instance().getTotalTime();
		} else {
			mouseRelease[i] = Time::instance().getTotalTime();
		}
	}

	mouseX = sfw::getMouseX();
	mouseY = sfw::getMouseY();
	return true;
}

bool Input::terminate() {
	return true;
}

bool Input::getKey( unsigned key ) {
	return keyPress[key] > keyRelease[key];
}

bool Input::getKeyPressed( unsigned key ) {
	return getKey(key) && !keyState[key];
}

bool Input::getKeyReleased( unsigned key ) {
	return !getKey( key ) && keyState[key];
}

bool Input::getMouseButton( unsigned key ) {
	return mousePress[key] > mouseRelease[key];
}

bool Input::getMouseButtonPressed( unsigned key ) {
	return getMouseButton( key ) && !mouseState[key];
}

bool Input::getMouseButtonReleased( unsigned key ) {
	return !getMouseButton( key ) && mouseState[key];
}

float Input::keyDelta( unsigned key ) {
	return keyPress[key] - keyRelease[key];
}

float Input::getMouseX() {
	return mouseX;
}

float Input::getMouseY() {
	return mouseY;
}

bool Input::isInitialized() {
	return initialized;
}