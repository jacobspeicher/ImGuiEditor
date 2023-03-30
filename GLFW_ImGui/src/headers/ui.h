#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "headers/imfilebrowser.h"
#include "headers/object_manager.h"
#include "headers/assets_manager.h"

#include <string>
#include <numbers>
#include <iostream>

namespace UI {
	void ShowMenu();
	void ShowSceneHeirarchy();
	void ShowAssets();
	void ShowInspector();
	void ShowFileDialog();

	void PopulateInspector(int id);

	bool* ShouldShowOverlay();
}