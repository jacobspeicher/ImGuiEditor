#include "headers/object_manager.h";

namespace ObjectManager {
	static ObjectMap objects;
	static int objectId = 0;

	void AddObjectToScene(ObjectType type, std::string defaultName) {
		SceneObject object;
		object.type = type;
		object.name = std::to_string(objectId) + " : " + defaultName;
		objects[objectId] = object;
		++objectId;
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

	ObjectType GetType(const ObjectMap::iterator& itr) { 
		return itr->second.type; 
	}
	ObjectType GetType(int id) { 
		return objects[id].type; 
	}

	glm::vec3 GetPosition(const ObjectMap::iterator& itr) { 
		return glm::vec3(itr->second.position[0], itr->second.position[1], itr->second.position[2]); 
	}
	glm::vec3 GetPosition(int id) { 
		return glm::vec3(objects[id].position[0], objects[id].position[1], objects[id].position[2]); 
	}

	glm::vec3 GetColor(const ObjectMap::iterator& itr) { 
		return glm::vec3(itr->second.color[0], itr->second.color[1], itr->second.color[2]); 
	}
	glm::vec3 GetColor(int id) { 
		return glm::vec3(objects[id].position[0], objects[id].position[1], objects[id].position[2]); 
	}

	float GetRotation(const ObjectMap::iterator& itr) { 
		return itr->second.rotation; 
	}
	float GetRotation(int id) { 
		return objects[id].rotation; 
	}

	int GetId(const ObjectMap::iterator& itr) {
		return itr->first;
	}

	std::string GetName(const ObjectMap::iterator& itr) {
		return itr->second.name;
	}
}