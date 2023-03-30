#ifndef ASSETS_MANAGER
#define ASSETS_MANAGER

#include <map>
#include <string>
#include "texture.h"

struct MaterialAsset {
	std::string name;

	GLuint diffuse;
	GLuint specular;
};

typedef std::map<int, MaterialAsset> MaterialMap;

namespace AssetsManager {
	void CreateMaterial();

	const MaterialMap::iterator GetMaterialsBegin();
	const MaterialMap::iterator GetMaterialsEnd();

	std::string GetMaterialName(const MaterialMap::iterator& itr);
}

#endif