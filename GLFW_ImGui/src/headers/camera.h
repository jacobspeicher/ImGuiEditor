#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// defines several possible options for camera movement
enum class CAMERA_MOVEMENT {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

// default camera volumes
const float YAW			=	-90.0f;
const float PITCH		=	0.0f;
const float SPEED		=	2.5f;
const float SENSITIVITY =	0.1f;
const float ZOOM		=	45.0f;

class Camera {
public:
	// camera attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// euler angles
	float Yaw;
	float Pitch;

	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// constructor with scalars
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH) :
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// returns the view matrix calculated using Euler angles and the LookAt matrix
	glm::mat4 GetViewMatrix() {
		return glm::lookAt(Position, Position + Front, Up);
	}

	// process input received from any keyboard-like input system
	// accepts input parameter in the form of a camera defined enum
	void ProcessKeyboard(CAMERA_MOVEMENT direction, float deltaTime) {
		float velocity = MovementSpeed * deltaTime;

		switch (direction) {
		case CAMERA_MOVEMENT::FORWARD:
			Position += Front * velocity;
			break;
		case CAMERA_MOVEMENT::BACKWARD:
			Position -= Front * velocity;
			break;
		case CAMERA_MOVEMENT::LEFT:
			Position -= Right * velocity;
			break;
		case CAMERA_MOVEMENT::RIGHT:
			Position += Right * velocity;
			break;
		}
	}

	// processes input received from a mouse input system, expects the offset value in both the x and y direction
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true) {
		xOffset *= MouseSensitivity;
		yOffset *= MouseSensitivity;

		Yaw += xOffset;
		Pitch += yOffset;

		// make sure that when the pitch is out of bounds, the screen doesn't get flipped
		if (constrainPitch) {
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			else if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// update Front, Right, and Up vectors using the updated Euler angles
		updateCameraVectors();
	}

	// process input recevied from a mouse scroll event, only requires input on the vertical wheel axis
	void ProcessMouseScroll(float yOffset) {
		Zoom -= (float)yOffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

private:
	// calculates the Front vector from the camera's Euler angles
	void updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

		// recalculates the Up and Right vectors
		Right = glm::normalize(glm::cross(Front, WorldUp)); // normalize so that movement doesn't get slowed when looking up or down
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif