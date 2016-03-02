#pragma once
#include <cassert>

#define INIT_ASSERT(name) assert(initialized && #name" is not initialized!")
/*
	There is only ever one window.
	Make details about the window accessible.
*/

/*
	Singleton Pattern:
		Private Constructors
		Public Static Accessor
*/

template<typename T>
class IWindow {
	unsigned width, height;
protected:
	IWindow() : initialized( false ) {}
public:
	bool initialized;
	static T& instance() {
		static T instance;
		return instance;
	}

	virtual bool initialize( unsigned width = 800, unsigned height = 600, const char* title = "Engine" ) = 0;
	virtual bool update() = 0;
	virtual void terminate() = 0;

	unsigned getWidth() { INIT_ASSERT(Window); return width; }
	unsigned getHeight() { INIT_ASSERT( Window ); return height; }
	bool isInitialized() { return initialized; }
};

// Curiously Recursive Template Pattern
class Window : public IWindow<Window> {
private:
	friend class IWindow<Window>;
	Window() {}

public:
	bool initialize( unsigned width = 800, unsigned height = 600, const char* title = "Engine" );
	bool update();
	void terminate();
};
