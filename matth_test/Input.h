#pragma once

class Input {
	bool initialized;
	Input() : initialized( false ) {}

	float keyRelease[400];
	float keyPress[400];
	bool keyState[400];

	float mouseRelease[10];
	float mousePress[10];
	bool mouseState[10];

	float mouseX, mouseY;
public:
	static Input& instance() { static Input instance; return instance; }

	bool initialize();
	bool update();
	bool terminate();
	bool isInitialized();

	bool getKey( unsigned key ); // true if key is down
	bool getKeyPressed( unsigned key ); // true on frame when key is pressed
	bool getKeyReleased( unsigned key ); // true on frame when key is released

	bool getMouseButton( unsigned key ); // true if key is down
	bool getMouseButtonPressed( unsigned key ); // true on frame when key is pressed
	bool getMouseButtonReleased( unsigned key ); // true on frame when key is released

	float keyDelta( unsigned key ); // returns difference between last press and release

	float getMouseX();
	float getMouseY();
};
