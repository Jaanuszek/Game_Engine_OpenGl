#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <unordered_map>
#include <functional>
#include <memory>

#include <GLFW/glfw3.h>

#include "Camera.h"

class InputHandler
{
private:
	bool m_cameraOn;
	bool m_firstMouse;
	float m_deltaTime;
	float lastX, lastY;
	GLFWwindow* m_window;
	std::shared_ptr<Camera> m_camera;
	std::unordered_map<int, std::function<void()>> m_CameraKeyBindings;
	std::unordered_map<int, std::function<void(int)>> m_keyActions;
	void InitializeKeyBindings();
public:
	InputHandler(GLFWwindow* window);
	~InputHandler();

	void setCamera(std::shared_ptr<Camera> cam);
	void setDeltaTime(float deltaTime);

	bool getCameraOn(void) const;
	void setCameraOn(bool cameraOn);
	bool getFirstMouse(void) const;

	void key_callback(int key, int action);
	void cameraMovement_callback();
	void mouse_callback(double xposIn, double yposIn);

	std::unordered_map<int, std::function<void(int)>> getKeyActions(void) const;

};
#endif 