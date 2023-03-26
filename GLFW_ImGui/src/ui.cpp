#include <string>

#include "headers/ui.h"
#include "headers/object_manager.h"

void UI::ShowSceneHeirarchy() {
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImVec2 workPos = viewport->WorkPos;
	ImVec2 windowPos = workPos;
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::Begin("Scene Heirarchy", NULL, windowFlags);
	if (ImGui::Button("Create")) {
		ImGui::OpenPopup("object_creation_popup");
	}
	if (ImGui::BeginPopup("object_creation_popup")) {
		ImGui::SeparatorText("Object");
		if (ImGui::Selectable("Triangle"))
			ObjectManager::AddObjectToScene(ObjectType::TRIANGLE, "Triangle");
		if (ImGui::Selectable("Cube"))
			ObjectManager::AddObjectToScene(ObjectType::CUBE, "Cube");
		ImGui::EndPopup();
	}

	ObjectMap::iterator itr = ObjectManager::GetBegin();
	while (itr != ObjectManager::GetEnd()) {
		if (ImGui::Selectable(ObjectManager::GetName(itr).c_str())) {

		}
		++itr;
	}

	ImGui::End();
}