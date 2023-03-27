#include "headers/ui.h"

namespace UI {
	static int selectedId = -1;
	static bool showOverlay = false;

	void ShowMenu() {
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New")) {}
				if (ImGui::MenuItem("Open")) {}
				if (ImGui::MenuItem("Save")) {}
				if (ImGui::MenuItem("Save As")) {}
				if (ImGui::MenuItem("Settings")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit")) {
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("View")) {
				ImGui::MenuItem("Debug Overlay", NULL, &showOverlay);
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	void ShowSceneHeirarchy() {
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_MenuBar;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 workPos = viewport->WorkPos;
		ImVec2 workSize = viewport->WorkSize;
		ImVec2 windowPos = workPos;
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(300, workSize.y));
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::Begin("Scene Heirarchy", NULL, windowFlags);

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Create SceneObject")) {
				ImGui::SeparatorText("2D");
				if (ImGui::MenuItem("Triangle"))
					ObjectManager::AddObjectToScene(ObjectType::TRIANGLE, "Triangle");
				ImGui::SeparatorText("3D");
				if (ImGui::MenuItem("Cube"))
					ObjectManager::AddObjectToScene(ObjectType::CUBE, "Cube");
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ObjectMap::iterator itr = ObjectManager::GetBegin();
		while (itr != ObjectManager::GetEnd()) {
			int id = ObjectManager::GetId(itr);
			std::string label = std::to_string(id) + " : " + ObjectManager::GetName(itr);

			bool selected = false;
			if (selectedId == id)
				selected = true;

			if (ImGui::Selectable(label.c_str(), selected)) {
				selectedId = id;
			}
			if (ImGui::BeginPopupContextItem()) {
				if (ImGui::Button("Delete")) {
					if (itr == ObjectManager::GetBegin()) {
						++itr;
					}
					else {
						--itr;
					}

					if (selectedId == id) {
						selectedId = -1;
					}
					ObjectManager::RemoveObjectFromScene(id);
				}
				ImGui::EndPopup();
			}

			if (ObjectManager::IsSceneEmpty()) {
				break;
			}

			++itr;
		}

		ImGui::End();
	}

	void ShowInspector() {
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 workPos = viewport->WorkPos;
		ImVec2 workSize = viewport->WorkSize;
		ImVec2 windowPos, windowPosPivot;
		windowPos.x = workPos.x + workSize.x;
		windowPos.y = workPos.y;
		windowPosPivot.x = 1.0f;
		windowPosPivot.y = 0.0f;
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
		ImGui::SetNextWindowSize(ImVec2(300, workSize.y));
		ImGui::SetNextWindowViewport(viewport->ID);
		
		ImGui::Begin("Inspector", NULL, windowFlags);
		
		if (selectedId == -1) {
			ImGui::Text("Select a SceneObject");
		}
		else {
			PopulateInspector(selectedId);
		}

		ImGui::End();
	}

	void PopulateInspector(int id) {
		static char nameInput[256];
		strcpy_s(nameInput, ObjectManager::GetName(id).c_str());

		ImGui::InputText("Name", nameInput, sizeof(nameInput));
		ObjectManager::SetName(id, nameInput);

		std::string idText = "ID: " + std::to_string(id);
		ImGui::Text(idText.c_str());

		ImGui::SeparatorText("Transform");

		ImGui::SliderFloat("rotation", ObjectManager::GetRotationRef(id), 0, 2 * std::numbers::pi);
		ImGui::SliderFloat3("position", ObjectManager::GetPositionRef(id), -1.0, 1.0);
		// ImGui::SliderFloat3("Scale");

		ImGui::SeparatorText("Attributes");
		ImGui::ColorEdit3("color", ObjectManager::GetColorRef(id));
	}

	bool* ShowOverlay() {
		return &showOverlay;
	}
}