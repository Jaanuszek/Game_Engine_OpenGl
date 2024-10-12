#include "../include/IO/InputHandler.h"

InputHandler::InputHandler(GLFWwindow* window)
	: m_cameraOn(false), m_firstMouse(true), m_deltaTime(0.0f), m_window(window), lastX(0.0f), lastY(0.0f), m_camera(nullptr), m_renderer(nullptr),
	m_GridLineOn(false), m_GridPointOn(false)
{
	InitializeKeyBindings();
}

InputHandler::~InputHandler()
{
}

bool InputHandler::getCameraOn(void) const
{
	return m_cameraOn;
}

bool InputHandler::getFirstMouse(void) const
{
	return m_firstMouse;
}

bool InputHandler::getTexture(void) const
{
	return m_Texture;
}

std::unordered_map<int, std::function<void(int)>> InputHandler::getKeyActions(void) const
{
	return m_keyActions;
}

void InputHandler::setCamera(std::shared_ptr<Camera> cam)
{
	m_camera = cam;
}
void InputHandler::setRenderer(std::shared_ptr<Renderer> renderer)
{
	m_renderer = renderer;
}
void InputHandler::setDeltaTime(double deltaTime)
{
	m_deltaTime = deltaTime;
}

void InputHandler::setCameraOn(bool cameraOn)
{
	m_cameraOn = cameraOn;
}

void InputHandler::key_callback(int key, int action)
{
	auto it = m_keyActions.find(key);
	if (it != m_keyActions.end()) {
		it->second(action);
	}
}

void InputHandler::cameraMovement_callback()
{
	bool actionHandled = false;
	for (const auto& keyBinding : m_CameraKeyBindings) {
		if (glfwGetKey(m_window, keyBinding.first) == GLFW_PRESS)
		{
			keyBinding.second();
			actionHandled = true;
		}
	}
	if (!actionHandled)
	{
		m_camera->processInput(Camera_Movement::NONE, m_deltaTime);
	}
}

void InputHandler::mouse_callback(double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (m_firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		m_firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	if (m_cameraOn) {
		m_camera->processMouseMovement(xoffset, yoffset);
	}
}

void InputHandler::InitializeKeyBindings()
{
	m_CameraKeyBindings = {
		{GLFW_KEY_W, [this]() { m_camera->processInput(Camera_Movement::FORWARD, m_deltaTime); }},
		{GLFW_KEY_S, [this]() { m_camera->processInput(Camera_Movement::BACKWARD, m_deltaTime); }},
		{GLFW_KEY_A, [this]() { m_camera->processInput(Camera_Movement::LEFT, m_deltaTime); }},
		{GLFW_KEY_D, [this]() { m_camera->processInput(Camera_Movement::RIGHT, m_deltaTime); }},
		{GLFW_KEY_LEFT_SHIFT, [this]() { m_camera->processInput(Camera_Movement::ACCELERATION, m_deltaTime); }},
	};

	m_keyActions = {
		{GLFW_KEY_C,[this](int action) { //enabling/disabling camera
			if (action == GLFW_PRESS)
			{
				m_cameraOn = !m_cameraOn;
				if (m_cameraOn)
				{
					glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					m_firstMouse = true;
				}
				else
				{
					glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				}
			}
		}},
		{GLFW_KEY_L,[this](int action) { //enabling linear Grid
			if (action == GLFW_PRESS)
			{
				m_GridLineOn = !m_GridLineOn;
				if (m_GridLineOn)
				{
					m_renderer->ShowGridLine();
				}
				else
				{
					m_renderer->DisableGrid();
				}
			}
		}},
		{GLFW_KEY_P,[this](int action) { //enabling point Grid
			if (action == GLFW_PRESS)
			{
				m_GridPointOn = !m_GridPointOn;
				if (m_GridPointOn)
				{
					m_renderer->ShowGridPoint();
				}
				else
				{
					m_renderer->DisableGrid();
				}
			}
		}},
		{GLFW_KEY_ESCAPE, [this](int action) {
			if (action == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(m_window, true);
			}
		}}
	};
}
