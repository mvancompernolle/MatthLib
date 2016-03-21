#include "Window.h"
#include "sfwdraw.h"

bool Window::initialize( unsigned width, unsigned height, const char* title ) {
	if ( initialized ) return true;
	this->width = width;
	this->height = height;
	initialized = sfw::initContext( width, height, title );
	return initialized;
}
bool Window::update() {
	INIT_ASSERT( Window );
	return sfw::stepContext();
}
void Window::terminate() {
	INIT_ASSERT( Window );
	sfw::termContext();
	initialized = false;
}