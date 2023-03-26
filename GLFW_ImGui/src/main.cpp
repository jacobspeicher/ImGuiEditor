#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <numbers>
#include <iostream>
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
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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
	basicShader.SetInt("material.shininess", 32.0f);
	basicShader.SetVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	basicShader.SetVec3("dirLight.ambient", glm::vec3(0.1f));
	basicShader.SetVec3("dirLight.diffuse", glm::vec3(0.2f));
	basicShader.SetVec3("dirLight.specular", glm::vec3(0.9f));
#pragma endregion Shader

#pragma region Rendering
	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	struct SceneObject {
		float position[3] = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;
		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	std::map<int, SceneObject> objects2D;
	std::map<int, SceneObject> objects3D;
	int numObjects2D = 0;
	int numObjects3D = 0;

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

		UI::ShowSceneHeirarchy();
		/*
		ImGui::Begin("Scene Heirarchy");
		
		if (ImGui::Button("New Triangle")) {
			SceneObject object;
			objects2D[numObjects2D] = object;
			++numObjects2D;
		}
		if (ImGui::Button("New Cube")) {
			SceneObject object;
			objects3D[numObjects3D] = object;
			++numObjects3D;
		}
		ImGui::End();
		*/

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, container.GetDiffuse());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, container.GetSpecular());

#pragma region RenderObjects
		ObjectMap::iterator itr = ObjectManager::GetBegin();
		while (itr != ObjectManager::GetEnd()) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, ObjectManager::GetPosition(itr));
			model = glm::rotate(model, ObjectManager::GetRotation(itr), glm::vec3(0.0f, 0.0f, 1.0f));

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

#pragma region Render2D
		/*glBindVertexArray(triangleVAO);

		colorShader.Use();

		for (int i = 0; i < numObjects2D; ++i) {
			// set up the gui
			std::string name = "Triangle " + std::to_string(i);
			ImGui::Begin(name.c_str());
			ImGui::SliderFloat("rotation", &objects2D[i].rotation, 0, 2 * std::numbers::pi);
			ImGui::SliderFloat3("position", objects2D[i].position, -1.0, 1.0);
			ImGui::ColorEdit3("color", objects2D[i].color);
			
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(objects2D[i].position[0], objects2D[i].position[1], objects2D[i].position[2]));
			model = glm::rotate(model, objects2D[i].rotation, glm::vec3(0.0f, 0.0f, 1.0f));
			colorShader.SetMat4("model", model);
			colorShader.SetVec3("color", glm::vec3(objects2D[i].color[0], objects2D[i].color[1], objects2D[i].color[2]));

			glDrawArrays(GL_TRIANGLES, 0, 3);

			ImGui::End();
		}*/
#pragma endregion Render2D

#pragma region Render3D
		/*glBindVertexArray(cubeVAO);

		basicShader.Use();
		basicShader.SetMat4("view", view);
		basicShader.SetMat4("projection", projection);
		basicShader.SetVec3("viewPos", camera.Position);

		for (int i = 0; i < numObjects3D; ++i) {
			// cube gui
			std::string name = "Cube " + std::to_string(i);
			ImGui::Begin(name.c_str());
			ImGui::SliderFloat("rotation", &objects3D[i].rotation, 0, 2 * std::numbers::pi);
			ImGui::SliderFloat3("position", objects3D[i].position, -1.0, 1.0);

			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(objects3D[i].position[0], objects3D[i].position[1], objects3D[i].position[2]));
			model = glm::rotate(model, objects3D[i].rotation, glm::vec3(0.0f, 0.0f, 1.0f));
			basicShader.SetMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);

			ImGui::End();
		}*/
#pragma endregion Render3D

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
	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}*/
	if (captureMouse) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera.ProcessKeyboard(LEFT, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera.ProcessKeyboard(RIGHT, deltaTime);
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