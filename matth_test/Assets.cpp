#include "Assets.h"
#include "sfwdraw.h"
#include "Window.h"
void Assets::loadTexture( const std::string& name, const char* path ) {
	assert( Window::instance().isInitialized() && "Window is not initialized!");
	Texture temp;
	// TODO: Error handling
	temp.handle = sfw::loadTextureMap( path );
	temp.height = sfw::getTextureHeight( temp.handle );
	temp.width = sfw::getTextureWidth( temp.handle );
	textures[name] = temp;
}

Assets::Texture Assets::getTexture( const std::string& name ) {
	const auto& texture = textures.find( name );
	if ( texture != textures.end() ) {
		return texture->second;
	}
	return Texture();
}

void Assets::drawTexture( const std::string& name, matth::mat3& matrix) {
	sfw::drawTextureMatrix( getTexture( name ).handle, 0.0f, WHITE, matth::mat4::mat3ToMat4(matrix) );
}