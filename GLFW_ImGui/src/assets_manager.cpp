#include "headers/assets_manager.h"

namespace AssetsManager {
	static MaterialMap materials;
	static int numMaterials;

	void CreateMaterial() {
		MaterialAsset material;
		material.name = "Material " + std::to_string(numMaterials);
		materials[numMaterials] = material;
		++numMaterials;
	}

	const MaterialMap::iterator GetMaterialsBegin() {
		return materials.begin();
	}
	const MaterialMap::iterator GetMaterialsEnd() {
		return materials.end();
	}

	std::string GetMaterialName(const MaterialMap::iterator& itr) {
		return itr->second.name;
	}
}