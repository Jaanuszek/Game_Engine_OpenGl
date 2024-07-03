#pragma once

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
private:
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraTarget;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_CameraRight;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraFront;
	glm::mat4 m_ViewMatrix;
	float cameraSpeed;

	glm::vec3 direction;
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool firstMouse = true;
public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget);
	glm::mat4 CalculateMVP(glm::mat4 proj, glm::mat4 model);
	void processInput(GLFWwindow* window, float deltaTime);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};