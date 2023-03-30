#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER

#include <glm/glm.hpp>
#include <map>
#include <string>
#include "headers/texture.h"

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

	Texture* texture = new Texture("gray.jpg", "gray.jpg");
};

typedef std::map<int, SceneObject> ObjectMap;

namespace ObjectManager {
	void AddObjectToScene(ObjectType type, std::string defaultName);
	void AddObjectToScene(const ObjectMap::iterator& itr);

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

	Texture* GetTexture(const ObjectMap::iterator& itr);
	Texture* GetTexture(int id);

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

	void SetDiffuse(const ObjectMap::iterator& itr, std::string diffuseFile);
	void SetDiffuse(int id, std::string diffuseFile);

	void SetSpecular(const ObjectMap::iterator& itr, std::string specularFile);
	void SetSpecular(int id, std::string specularFile);
}

#endif