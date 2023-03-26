#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER

#include <glm/glm.hpp>
#include <map>
#include <string>

enum class ObjectType {
	// 2D
	TRIANGLE,
	// 3D
	CUBE,
};

struct SceneObject {
	ObjectType type;
	std::string name;
	float position[3] = { 0.0f, 0.0f, 0.0f };
	float rotation = 0.0f;
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
};

typedef std::map<int, SceneObject> ObjectMap;

namespace ObjectManager {
	void AddObjectToScene(ObjectType type, std::string defaultName);

	void RemoveObjectFromScene(int id);

	const ObjectMap::iterator GetBegin();

	const ObjectMap::iterator GetEnd();

	ObjectType GetType(const ObjectMap::iterator& itr);
	ObjectType GetType(int id);

	glm::vec3 GetPosition(const ObjectMap::iterator& itr);
	glm::vec3 GetPosition(int id);

	glm::vec3 GetColor(const ObjectMap::iterator& itr);
	glm::vec3 GetColor(int id);

	float GetRotation(const ObjectMap::iterator& itr);
	float GetRotation(int id);

	int GetId(const ObjectMap::iterator& itr);

	std::string GetName(const ObjectMap::iterator& itr);
}

#endif