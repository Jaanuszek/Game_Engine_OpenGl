#pragma once

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


enum class Camera_Movement{
	NONE,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ACCELERATION,
	ON,
	OFF
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;



class Camera {
private:
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraTarget;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_CameraRight;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraFront;
	glm::mat4 m_ViewMatrix;

	float yaw;
	float pitch;

	float cameraSpeed;
	float MouseSensitivity;
	float Zoom;

	void updateCameraVectors();
public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget);
	glm::mat4 CalculateMVP(glm::mat4 proj, glm::mat4 model);
	void processInput(Camera_Movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset);
	glm::vec3 GetCameraPos(void) const;
};
