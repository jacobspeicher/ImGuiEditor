#include "headers/object_manager.h";

namespace ObjectManager {
	static ObjectMap objects;
	static int objectId = 0;

	void AddObjectToScene(ObjectType type, std::string defaultName) {
		SceneObject object;
		object.type = type;
		object.name = defaultName;
		objects[objectId] = object;
		++objectId;
	}

	void RemoveObjectFromScene(const ObjectMap::iterator& itr) {
		objects.erase(itr);
	}
	void RemoveObjectFromScene(int id) {
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

	glm::vec3 GetColor(const ObjectMap::iterator& itr) { 
		return glm::vec3(itr->second.color[0], itr->second.color[1], itr->second.color[2]); 
	}
	glm::vec3 GetColor(int id) { 
		return glm::vec3(objects.at(id).position[0], objects.at(id).position[1], objects.at(id).position[2]); 
	}

	float GetRotation(const ObjectMap::iterator& itr) { 
		return itr->second.rotation; 
	}
	float GetRotation(int id) { 
		return objects.at(id).rotation; 
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
		return &itr->second.rotation;
	}
	float* GetRotationRef(int id) {
		return &objects.at(id).rotation;
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
#pragma endregion Setters
}