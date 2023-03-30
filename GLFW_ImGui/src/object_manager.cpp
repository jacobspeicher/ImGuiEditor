#include "headers/object_manager.h";

namespace ObjectManager {
	static ObjectMap objects;
	static std::map<int, int> copies;
	static int objectId = 0;

	void AddObjectToScene(ObjectType type, std::string defaultName) {
		//Texture texture("gray.jpg", "gray.jpg");

		SceneObject object;
		object.type = type;
		object.name = defaultName;
		//object.diffuse = texture.GetDiffuse();
		//object.specular = texture.GetSpecular();

		objects[objectId] = object;
		copies[objectId] = 0;
		++objectId;
	}
	void AddObjectToScene(const ObjectMap::iterator& itr) {
		SceneObject object;
		copies[GetId(itr)]++;

		object.type = itr->second.type;
		object.name = itr->second.name + " " + std::to_string(copies[GetId(itr)]);
		object.visible = itr->second.visible;
		std::copy(std::begin(itr->second.position), std::end(itr->second.position), std::begin(object.position));
		std::copy(std::begin(itr->second.rotation), std::end(itr->second.rotation), std::begin(object.rotation));
		std::copy(std::begin(itr->second.scale), std::end(itr->second.scale), std::begin(object.scale));
		std::copy(std::begin(itr->second.color), std::end(itr->second.color), std::begin(object.color));

		objects[objectId] = object;
		++objectId;
	}

	void RemoveObjectFromScene(const ObjectMap::iterator& itr) {
		delete itr->second.texture;
		objects.erase(itr);
	}
	void RemoveObjectFromScene(int id) {
		delete objects.at(id).texture;
		objects.erase(id);
	}

	const ObjectMap::iterator GetBegin() {
		return objects.begin();
	}
	const ObjectMap::iterator GetEnd() {
		return objects.end();
	}

	bool IsSceneEmpty() {
		return objects.size() == 0;
	}

#pragma region Getters
	int GetId(const ObjectMap::iterator& itr) {
		return itr->first;
	}

	ObjectType GetType(const ObjectMap::iterator& itr) { 
		return itr->second.type; 
	}
	ObjectType GetType(int id) { 
		return objects.at(id).type; 
	}

	std::string GetName(const ObjectMap::iterator& itr) {
		return itr->second.name;
	}
	std::string GetName(int id) {
		return objects.at(id).name;
	}

	bool GetVisible(const ObjectMap::iterator& itr) {
		return itr->second.visible;
	}
	bool GetVisible(int id) {
		return objects.at(id).visible;
	}

	glm::vec3 GetPosition(const ObjectMap::iterator& itr) { 
		return glm::vec3(itr->second.position[0], itr->second.position[1], itr->second.position[2]); 
	}
	glm::vec3 GetPosition(int id) { 
		return glm::vec3(objects.at(id).position[0], objects.at(id).position[1], objects.at(id).position[2]); 
	}

	glm::vec3 GetRotation(const ObjectMap::iterator& itr) { 
		return glm::vec3(itr->second.rotation[0], itr->second.rotation[1], itr->second.rotation[2]);
	}
	glm::vec3 GetRotation(int id) { 
		return glm::vec3(objects.at(id).rotation[0], objects.at(id).rotation[1], objects.at(id).rotation[2]);
	}

	glm::vec3 GetScale(const ObjectMap::iterator& itr) {
		return glm::vec3(itr->second.scale[0], itr->second.scale[1], itr->second.scale[2]);
	}
	glm::vec3 GetScale(int id) {
		return glm::vec3(objects.at(id).scale[0], objects.at(id).scale[1], objects.at(id).scale[2]);
	}

	glm::vec3 GetColor(const ObjectMap::iterator& itr) {
		return glm::vec3(itr->second.color[0], itr->second.color[1], itr->second.color[2]);
	}
	glm::vec3 GetColor(int id) {
		return glm::vec3(objects.at(id).position[0], objects.at(id).position[1], objects.at(id).position[2]);
	}

	Texture* GetTexture(const ObjectMap::iterator& itr) {
		return itr->second.texture;
	}
	Texture* GetTexture(int id) {
		return objects.at(id).texture;
	}
#pragma endregion Getters

#pragma region ReferenceGetters
	bool* GetVisibleRef(const ObjectMap::iterator& itr) {
		return &itr->second.visible;
	}
	bool* GetVisibleRef(int id) {
		return &objects.at(id).visible;
	}

	float* GetPositionRef(const ObjectMap::iterator& itr) {
		return itr->second.position;
	}
	float* GetPositionRef(int id) {
		return objects.at(id).position;
	}

	float* GetRotationRef(const ObjectMap::iterator& itr) {
		return itr->second.rotation;
	}
	float* GetRotationRef(int id) {
		return objects.at(id).rotation;
	}

	float* GetScaleRef(const ObjectMap::iterator& itr) {
		return itr->second.scale;
	}
	float* GetScaleRef(int id) {
		return objects.at(id).scale;
	}

	float* GetColorRef(const ObjectMap::iterator& itr) {
		return itr->second.color;
	}
	float* GetColorRef(int id) {
		return objects.at(id).color;
	}
#pragma endregion ReferenceGetters

#pragma region Setters
	void SetName(const ObjectMap::iterator& itr, std::string nameInput) {
		itr->second.name = nameInput;
	}
	void SetName(int id, std::string nameInput) {
		objects.at(id).name = nameInput;
	}

	void SetDiffuse(const ObjectMap::iterator& itr, std::string diffuseFile) {
		itr->second.texture->SetDiffuse(diffuseFile);
	}
	void SetDiffuse(int id, std::string diffuseFile) {
		objects.at(id).texture->SetDiffuse(diffuseFile);
	}

	void SetSpecular(const ObjectMap::iterator& itr, std::string specularFile) {
		itr->second.texture->SetSpecular(specularFile);
	}
	void SetSpecular(int id, std::string specularFile) {
		objects.at(id).texture->SetDiffuse(specularFile);
	}
#pragma endregion Setters
}