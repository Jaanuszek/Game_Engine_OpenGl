#include "Camera.h"

void Camera::updateCameraVectors()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_CameraFront = glm::normalize(direction);
	m_CameraRight = glm::normalize(glm::cross(m_CameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
}

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget) : m_CameraPos(cameraPos), m_CameraTarget(cameraTarget), yaw(YAW), pitch(PITCH), cameraSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	updateCameraVectors();
	m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraTarget + m_CameraFront, m_CameraUp); //view matrix, look at matrix
}

glm::mat4 Camera::CalculateMVP(glm::mat4 proj, glm::mat4 model)
{
	m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
	return proj * m_ViewMatrix * model;
}

glm::vec3 Camera::GetCameraPos(void) const
{
	return m_CameraPos;
}

void Camera::processInput(Camera_Movement direction, float deltaTime)
{
	//float cameraSpeed = 2.5f * deltaTime;
	if (direction == Camera_Movement::FORWARD)
		m_CameraPos += cameraSpeed * m_CameraFront;
	if (direction == Camera_Movement::BACKWARD)
		m_CameraPos -= cameraSpeed * m_CameraFront;
	if (direction == Camera_Movement::LEFT)
		m_CameraPos -= m_CameraRight * cameraSpeed;
	if (direction == Camera_Movement::RIGHT)	
		m_CameraPos += m_CameraRight* cameraSpeed;
	if (direction == Camera_Movement::ACCELERATION)
		cameraSpeed = 10.0f * deltaTime;
	else
		cameraSpeed = 2.5f * deltaTime;	
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;
	
	yaw += xoffset;
	pitch += yoffset;
	if(pitch>89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	updateCameraVectors();
}


