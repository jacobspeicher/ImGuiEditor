#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <numbers>
#include <iostream>

#include "utilities/stb_image.h"
#include "shader.h"
#include "camera.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <map>

float vertices[] =
{
	// pos					 // texture coords
	-0.5f,	-0.5f,	-0.5f,	 0.0f,	 0.0f,	 // bottom left
	 0.5f,	-0.5f,	-0.5f,	 1.0f,	 0.0f,	 // bottom right
	 0.5f,	 0.5f,	-0.5f,	 1.0f,	 1.0f,	 // top right
	 0.5f,	 0.5f,	-0.5f,	 1.0f,	 1.0f,	 // top right
	-0.5f,	 0.5f,	-0.5f,	 0.0f,	 1.0f,	 // top left
	-0.5f,	-0.5f,	-0.5f,	 0.0f,	 0.0f,	 // bottom left

	-0.5f,	-0.5f,	 0.5f,	 0.0f,	 0.0f,	 // bottom left
	 0.5f,	-0.5f,	 0.5f,	 1.0f,	 0.0f,	 // bottom right
	 0.5f,	 0.5f,	 0.5f,	 1.0f,	 1.0f,	 // top right
	 0.5f,	 0.5f,	 0.5f,	 1.0f,	 1.0f,	 // top right
	-0.5f,	 0.5f,	 0.5f,	 0.0f,	 1.0f,	 // top left
	-0.5f,	-0.5f,	 0.5f,	 0.0f,	 0.0f,	 // bottom left

	-0.5f,	 0.5f,	 0.5f,	 1.0f,	 0.0f,	 // bottom left
	-0.5f,	 0.5f,	-0.5f,	 1.0f,	 1.0f,	 // bottom right
	-0.5f,	-0.5f,	-0.5f,	 0.0f,	 1.0f,	 // top right
	-0.5f,	-0.5f,	-0.5f,	 0.0f,	 1.0f,	 // top right
	-0.5f,	-0.5f,	 0.5f,	 0.0f,	 0.0f,	 // top left
	-0.5f,	 0.5f,	 0.5f,	 1.0f,	 0.0f,	 // bottom left

	 0.5f,	 0.5f,	 0.5f,	 1.0f,	 0.0f,	 // bottom left
	 0.5f,	 0.5f,	-0.5f,	 1.0f,	 1.0f,	 // bottom right
	 0.5f,	-0.5f,	-0.5f,	 0.0f,	 1.0f,	 // top right
	 0.5f,	-0.5f,	-0.5f,	 0.0f,	 1.0f,	 // top right
	 0.5f,	-0.5f,	 0.5f,	 0.0f,	 0.0f,	 // top left
	 0.5f,	 0.5f,	 0.5f,	 1.0f,	 0.0f,	 // bottom left

	-0.5f,	-0.5f,	-0.5f,	 0.0f,	 1.0f,	 // bottom left
	 0.5f,	-0.5f,	-0.5f,	 1.0f,	 1.0f,	 // bottom right
	 0.5f,	-0.5f,	 0.5f,	 1.0f,	 0.0f,	 // top right
	 0.5f,	-0.5f,	 0.5f,	 1.0f,	 0.0f,	 // top right
	-0.5f,	-0.5f,	 0.5f,	 0.0f,	 0.0f,	 // top left
	-0.5f,	-0.5f,	-0.5f,	 0.0f,	 1.0f,	 // bottom left

	-0.5f,	 0.5f,	-0.5f,	 0.0f,	 1.0f,	 // bottom left
	 0.5f,	 0.5f,	-0.5f,	 1.0f,	 1.0f,	 // bottom right
	 0.5f,	 0.5f,	 0.5f,	 1.0f,	 0.0f,	 // top right
	 0.5f,	 0.5f,	 0.5f,	 1.0f,	 0.0f,	 // top right
	-0.5f,	 0.5f,	 0.5f,	 0.0f,	 0.0f,	 // top left
	-0.5f,	 0.5f,	-0.5f,	 0.0f,	 1.0f, 	 // bottom left
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

float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f; // time of last frame

// callback signatures
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);
void capture_mouse(GLFWwindow* window, GLFWcursorposfun callback);

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

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
#pragma endregion Binding

#pragma region Shader
	Shader colorShader("color.vert", "color.frag");
#pragma endregion Shader

#pragma region Rendering
	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	struct SceneObject {
		float position[2] = { 0.0f, 0.0f };
		float rotation = 0.0f;
		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	std::map<int, SceneObject> objects;
	int numObjects = 0;

	// application loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// feed inputs to imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glBindVertexArray(triangleVAO);

		colorShader.Use();

		ImGui::Begin("Scene Heirarchy");
		if (ImGui::Button("Create Triangle")) {
			ImGui::SameLine();
			ImGui::Text("clicked");
			SceneObject object;
			objects[numObjects] = object;
			++numObjects;
		}
		ImGui::End();

		for (int i = 0; i < numObjects; ++i) {
			// set up the gui
			ImGui::Begin("Triangle " + i);
			ImGui::SliderFloat("rotation", &objects[i].rotation, 0, 2 * std::numbers::pi);
			ImGui::SliderFloat2("position", objects[i].position, -1.0, 1.0);
			ImGui::ColorEdit3("color", objects[i].color);

			glm::mat4 model = glm::mat4(1.0f);
			
			model = glm::translate(model, glm::vec3(objects[i].position[0], objects[i].position[1], 0.0f));
			model = glm::rotate(model, objects[i].rotation, glm::vec3(0.0f, 0.0f, 1.0f));
			colorShader.SetMat4("model", 1, model);
			colorShader.SetVec3("color", 1, glm::vec3(objects[i].color[0], objects[i].color[1], objects[i].color[2]));

			glDrawArrays(GL_TRIANGLES, 0, 3);

			ImGui::End();
		}

		ImGui::ShowDemoWindow();

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

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void capture_mouse(GLFWwindow* window, GLFWcursorposfun callback) {}