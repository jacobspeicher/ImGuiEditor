#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "headers/object_manager.h"

#include <string>
#include <numbers>

namespace UI {
	void ShowMenu();
	void ShowSceneHeirarchy();
	void ShowInspector();
	void PopulateInspector(int id);
}