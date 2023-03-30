#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <numbers>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

#include "utilities/stb_image.h"
#include "headers/shader.h"
#include "headers/texture.h"
#include "headers/camera.h"
#include "headers/ui.h"
#include "headers/object_manager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

float vertices[] =
{
	// pos					// cube face normals	 // texture coords
	-0.5f,	-0.5f,	-0.5f,   0.0f,   0.0f,  -1.0f,	 0.0f,	 0.0f,	// bottom left
	 0.5f,	-0.5f,	-0.5f,   0.0f,   0.0f,  -1.0f,	 1.0f,	 0.0f,	// bottom right
	 0.5f,	 0.5f,	-0.5f,   0.0f,   0.0f,  -1.0f,	 1.0f,	 1.0f,	// top right
	 0.5f,	 0.5f,	-0.5f,   0.0f,   0.0f,  -1.0f,	 1.0f,	 1.0f,	// top right
	-0.5f,	 0.5f,	-0.5f,   0.0f,   0.0f,  -1.0f,	 0.0f,	 1.0f,	// top left
	-0.5f,	-0.5f,	-0.5f,   0.0f,   0.0f,  -1.0f,	 0.0f,	 0.0f,	// bottom left

	-0.5f,	-0.5f,	 0.5f,   0.0f,   0.0f,   1.0f,	 0.0f,	 0.0f,	// bottom left
	 0.5f,	-0.5f,	 0.5f,   0.0f,   0.0f,   1.0f,	 1.0f,	 0.0f,	// bottom right
	 0.5f,	 0.5f,	 0.5f,   0.0f,   0.0f,   1.0f,	 1.0f,	 1.0f,	// top right
	 0.5f,	 0.5f,	 0.5f,   0.0f,   0.0f,   1.0f,	 1.0f,	 1.0f,	// top right
	-0.5f,	 0.5f,	 0.5f,   0.0f,   0.0f,   1.0f,	 0.0f,	 1.0f,	// top left
	-0.5f,	-0.5f,	 0.5f,   0.0f,   0.0f,   1.0f,	 0.0f,	 0.0f,	// bottom left

	-0.5f,	 0.5f,	 0.5f,  -1.0f,   0.0f,   0.0f,	 0.0f,	 0.0f,	// bottom left
	-0.5f,	 0.5f,	-0.5f,  -1.0f,   0.0f,   0.0f,	 1.0f,	 0.0f,	// bottom right
	-0.5f,	-0.5f,	-0.5f,  -1.0f,   0.0f,   0.0f,	 1.0f,	 1.0f,	// top right
	-0.5f,	-0.5f,	-0.5f,  -1.0f,   0.0f,   0.0f,	 1.0f,	 1.0f,	// top right
	-0.5f,	-0.5f,	 0.5f,  -1.0f,   0.0f,   0.0f,	 0.0f,	 1.0f,	// top left
	-0.5f,	 0.5f,	 0.5f,  -1.0f,   0.0f,   0.0f,	 0.0f,	 0.0f,	// bottom left

	 0.5f,	 0.5f,	 0.5f,   1.0f,   0.0f,   0.0f,	 0.0f,	 0.0f,	// bottom left
	 0.5f,	 0.5f,	-0.5f,   1.0f,   0.0f,   0.0f,	 1.0f,	 0.0f,	// bottom right
	 0.5f,	-0.5f,	-0.5f,   1.0f,   0.0f,   0.0f,	 1.0f,	 1.0f,	// top right
	 0.5f,	-0.5f,	-0.5f,   1.0f,   0.0f,   0.0f,	 1.0f,	 1.0f,	// top right
	 0.5f,	-0.5f,	 0.5f,   1.0f,   0.0f,   0.0f,	 0.0f,	 1.0f,	// top left
	 0.5f,	 0.5f,	 0.5f,   1.0f,   0.0f,   0.0f,	 0.0f,	 0.0f,	// bottom left

	-0.5f,	-0.5f,	-0.5f,   0.0f,   -1.0f,   0.0f,	 0.0f,	 0.0f,	// bottom left
	 0.5f,	-0.5f,	-0.5f,   0.0f,   -1.0f,   0.0f,	 1.0f,	 0.0f,	// bottom right
	 0.5f,	-0.5f,	 0.5f,   0.0f,   -1.0f,   0.0f,	 1.0f,	 1.0f,	// top right
	 0.5f,	-0.5f,	 0.5f,   0.0f,   -1.0f,   0.0f,	 1.0f,	 1.0f,	// top right
	-0.5f,	-0.5f,	 0.5f,   0.0f,   -1.0f,   0.0f,	 0.0f,	 1.0f,	// top left
	-0.5f,	-0.5f,	-0.5f,   0.0f,   -1.0f,   0.0f,	 0.0f,	 0.0f,	// bottom left

	-0.5f,	 0.5f,	-0.5f,   0.0f,    1.0f,   0.0f,	 0.0f,	 0.0f,	// bottom left
	 0.5f,	 0.5f,	-0.5f,   0.0f,    1.0f,   0.0f,	 1.0f,	 0.0f,	// bottom right
	 0.5f,	 0.5f,	 0.5f,   0.0f,    1.0f,   0.0f,	 1.0f,	 1.0f,	// top right
	 0.5f,	 0.5f,	 0.5f,   0.0f,    1.0f,   0.0f,	 1.0f,	 1.0f,	// top right
	-0.5f,	 0.5f,	 0.5f,   0.0f,    1.0f,   0.0f,	 0.0f,	 1.0f,	// top left
	-0.5f,	 0.5f,	-0.5f,   0.0f,    1.0f,   0.0f,	 0.0f,	 0.0f,	// bottom left
};

float triangleVertices[] = {
	// pos					color
	-1.0f,	0.5f,	0.0f,	1.0f,	0.0f,	0.0f, // left
	-0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f, // top
	0.0f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f, // right
};

float mixFactor = 0.2f;
float screenWidth = 1200;
float screenHeight = 720.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = screenWidth / 2;
float lastY = screenHeight / 2;
bool firstMouse = true;
bool captureMouse = false;

float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f; // time of last frame

// callback signatures
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);
void capture_mouse(GLFWwindow* window, bool mouseCaptured);

// helpers
std::string convertVec3ToString(glm::vec3 vec);

int main(int argc, char* argv) {
#pragma region Init
	// initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a window
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Little Editor", NULL, NULL);
	if (window == NULL) {
		std::cout << "ERROR::WINDOW : FAILED TO CREATE" << std::endl;
		glfwTerminate();
		return -1;
	}

	// make the window the current context
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	capture_mouse(window, captureMouse);

	// initalize GLAD for function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR::GLAD : FAILED TO LOAD PROCESS" << std::endl;
		glfwTerminate();
		return -1;
	}

	//glViewport(100, 100, 300, 300);

	// initialize dear imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	
	// setup platform/renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// setup imgui style
	ImGui::StyleColorsDark();
#pragma endregion Init

#pragma region Binding
	unsigned int triangleVAO;
	unsigned int triangleVBO;

	glGenVertexArrays(1, &triangleVAO);
	glGenBuffers(1, &triangleVBO);

	// bind triangle object
	glBindVertexArray(triangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

	// copy vertex data into the VAO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	// interpret the vertex data for positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// enable the vertex attrib with the vertex attrib location
	glEnableVertexAttribArray(0);

	// interpret the vertex data for colors and enable
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int cubeVAO, cubeVBO;

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);

	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
#pragma endregion Binding

#pragma region Textures
	Texture container("assets/container_diffuse.png", "assets/container_specular.png");
#pragma endregion Textures

#pragma region Shader
	Shader colorShader("shaders/color.vert", "shaders/color.frag");
	Shader basicShader("shaders/basic.vert", "shaders/basic.frag");

	basicShader.Use();
	basicShader.SetInt("material.diffuse", 0);
	basicShader.SetInt("material.specular", 1);
	basicShader.SetInt("material.shininess", 256.0f);
	basicShader.SetVec3("dirLight.direction", glm::vec3(-1.0f, -1.0f, 0.0f));
	basicShader.SetVec3("dirLight.ambient", glm::vec3(0.2f));
	basicShader.SetVec3("dirLight.diffuse", glm::vec3(0.5f));
	basicShader.SetVec3("dirLight.specular", glm::vec3(0.1f));
#pragma endregion Shader

#pragma region Rendering
	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// application loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// feed inputs to imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), screenWidth / screenHeight, 0.1f, 100.0f);

		UI::ShowMenu();
		UI::ShowSceneHeirarchy();
		UI::ShowInspector();
		UI::ShowAssets();
		UI::ShowFileDialog();

#pragma region Debug
		if (*UI::ShouldShowOverlay()) {
			ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration |
				ImGuiWindowFlags_NoDocking |
				ImGuiWindowFlags_AlwaysAutoResize |
				ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_NoFocusOnAppearing |
				ImGuiWindowFlags_NoNav |
				ImGuiWindowFlags_NoMove;
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImVec2 workPos = viewport->WorkPos;
			ImVec2 workSize = viewport->WorkSize;
			ImVec2 windowPos, windowPosPivot;
			windowPos = ImVec2(workPos.x + workSize.x, workPos.y + workSize.y);
			windowPosPivot = ImVec2(1.0f, 1.0f);
			ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
			ImGui::SetNextWindowViewport(viewport->ID);

			if (ImGui::Begin("Debug Overlay", UI::ShouldShowOverlay(), windowFlags)) {
				ImGui::Text("Camera View: ");
				ImGui::SameLine();
				ImGui::Text(convertVec3ToString(camera.Front).c_str());

				ImGui::Text("Light Direction: ");
				ImGui::SameLine();
				ImGui::Text(convertVec3ToString(glm::vec3(-1.0f, 0.0f, 0.0f)).c_str());

				glm::vec3 reflect = glm::reflect(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
				float dotProduct = glm::dot(camera.Front, reflect);
				ImGui::Text("reflect: ");
				ImGui::SameLine();
				ImGui::Text(convertVec3ToString(reflect).c_str());
				ImGui::Text("(viewDir)x(reflect) Dot Product: ");
				ImGui::SameLine();
				ImGui::Text(std::to_string(dotProduct).c_str());
			}
			ImGui::End();
		}
#pragma endregion Debug

#pragma region RenderObjects
		ObjectMap::iterator itr = ObjectManager::GetBegin();
		while (itr != ObjectManager::GetEnd()) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, ObjectManager::GetPosition(itr));

			glm::vec3 rotation = ObjectManager::GetRotation(itr);
			model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			model = glm::scale(model, ObjectManager::GetScale(itr));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, container.GetDiffuse());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, container.GetSpecular());

			switch (ObjectManager::GetType(itr)) {
			case ObjectType::TRIANGLE:
				glBindVertexArray(triangleVAO);

				colorShader.Use();
				colorShader.SetMat4("model", model);
				colorShader.SetVec3("color", ObjectManager::GetColor(itr));

				glDrawArrays(GL_TRIANGLES, 0, 3);
				break;
			case ObjectType::CUBE:

				glBindVertexArray(cubeVAO);

				basicShader.Use();
				basicShader.SetMat4("view", view);
				basicShader.SetMat4("projection", projection);
				basicShader.SetVec3("viewPos", camera.Position);
				basicShader.SetMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
				break;
			}
			++itr;
		}
#pragma endregion RenderObjects

		// ImGui::ShowDemoWindow();

		// render imgui to the screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
#pragma endregion Rendering

	// destroy imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xPos = static_cast<float>(xposIn);
	float yPos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.ProcessMouseScroll(static_cast<float>(yOffset));
}

void processInput(GLFWwindow* window) {
	if (captureMouse) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera.ProcessKeyboard(CAMERA_MOVEMENT::FORWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera.ProcessKeyboard(CAMERA_MOVEMENT::BACKWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera.ProcessKeyboard(CAMERA_MOVEMENT::LEFT, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera.ProcessKeyboard(CAMERA_MOVEMENT::RIGHT, deltaTime);
		}
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		capture_mouse(window, !captureMouse);
		
		if (!captureMouse) {
			ImGui_ImplGlfw_RestoreCallbacks(window);
			ImGui_ImplGlfw_InstallCallbacks(window);
		}
	}
}

void capture_mouse(GLFWwindow* window, bool mouseCaptured) {
	captureMouse = mouseCaptured;

	if (captureMouse) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorPosCallback(window, NULL);
		glfwSetScrollCallback(window, NULL);
		firstMouse = true;
	}
}

std::string convertVec3ToString(glm::vec3 vec) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);
	std::string output = "(";
	for (int i = 0; i < 3; ++i) {
		ss << vec[i];
		output += ss.str();
		if (i < 2)
			output += ", ";
		ss.str("");
	}
	output += ")";
	return output;
}