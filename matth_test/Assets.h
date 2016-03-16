#pragma once
#include <unordered_map>
#include "matth.h"

class Assets {
	Assets() {}
public:
	struct Texture {
		unsigned width, height, handle;
	};

	std::unordered_map<std::string, Texture> textures;
	void loadTexture( const std::string& name, const char* path );
	Texture getTexture(const std::string& name);
	void drawTexture( const std::string& name, matth::mat3& matrix = matth::mat3::identity());
	static Assets& instance() {
		static Assets i; return i;
	}
};