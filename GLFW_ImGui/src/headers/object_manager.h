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
	int id;
	ObjectType type;
	std::string name;
	bool visible;

	float position[3] = { 0.0f, 0.0f, 0.0f };
	float rotation[3] = { 0.0f, 0.0f, 0.0f };
	float scale[3] = { 1.0f, 1.0f, 1.0f };

	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
};

typedef std::map<int, SceneObject> ObjectMap;

namespace ObjectManager {
	void AddObjectToScene(ObjectType type, std::string defaultName);

	void RemoveObjectFromScene(const ObjectMap::iterator& itr);
	void RemoveObjectFromScene(int id);

	const ObjectMap::iterator GetBegin();
	const ObjectMap::iterator GetEnd();

	bool IsSceneEmpty();

	// object property getters
	int GetId(const ObjectMap::iterator& itr);

	ObjectType GetType(const ObjectMap::iterator& itr);
	ObjectType GetType(int id);

	std::string GetName(const ObjectMap::iterator& itr);
	std::string GetName(int id);

	bool GetVisible(const ObjectMap::iterator& itr);
	bool GetVisible(int id);

	glm::vec3 GetPosition(const ObjectMap::iterator& itr);
	glm::vec3 GetPosition(int id);

	glm::vec3 GetRotation(const ObjectMap::iterator& itr);
	glm::vec3 GetRotation(int id);

	glm::vec3 GetScale(const ObjectMap::iterator& itr);
	glm::vec3 GetScale(int id);

	glm::vec3 GetColor(const ObjectMap::iterator& itr);
	glm::vec3 GetColor(int id);

	// object property references (for imgui controls)
	bool* GetVisibleRef(const ObjectMap::iterator& itr);
	bool* GetVisibleRef(int id);

	float* GetPositionRef(const ObjectMap::iterator& itr);
	float* GetPositionRef(int id);

	float* GetRotationRef(const ObjectMap::iterator& itr);
	float* GetRotationRef(int id);

	float* GetScaleRef(const ObjectMap::iterator& itr);
	float* GetScaleRef(int id);

	float* GetColorRef(const ObjectMap::iterator& itr);
	float* GetColorRef(int id);

	// object property setters
	void SetName(const ObjectMap::iterator& itr, std::string nameInput);
	void SetName(int id, std::string nameInput);
}

#endif