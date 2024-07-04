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
	//m_CameraDirection = glm::normalize(m_CameraPos - m_CameraTarget); //direction we are moving in negative z axis so object will move from us 
	//m_CameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_CameraDirection)); //x-axis right vector we get it by cross product of up vector and direction vector
	//m_CameraUp = glm::cross(m_CameraDirection, m_CameraRight); //up vector y-axis
	//m_CameraFront = glm::normalize(m_CameraDirection - m_CameraPos); //front vector

	updateCameraVectors();
	m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraTarget + m_CameraFront, m_CameraUp); //view matrix, look at matrix
}
glm::mat4 Camera::CalculateMVP(glm::mat4 proj, glm::mat4 model)
{
	m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
	return proj * m_ViewMatrix * model;
}

void Camera::processInput(GLFWwindow* window, float deltaTime)
{
	//float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_CameraPos += cameraSpeed * m_CameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_CameraPos -= cameraSpeed * m_CameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_CameraPos -= m_CameraRight * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	
		m_CameraPos += m_CameraRight* cameraSpeed;
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraSpeed = 10.0f * deltaTime;
	else
		cameraSpeed = 2.5f * deltaTime;	
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	
	yaw += xoffset;
	pitch += yoffset;
	if(pitch>89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	updateCameraVectors();
}


