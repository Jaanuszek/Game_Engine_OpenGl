#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <unordered_map>
#include <functional>
#include <memory>
#include "Renderer.h"
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
	std::shared_ptr<Renderer> m_renderer;
	bool m_GridLineOn;
	bool m_GridPointOn;
	bool m_Texture; //for now i have only 2 options, so i will use bool, but later i will proprably change it to enum
	void InitializeKeyBindings();
public:
	InputHandler(GLFWwindow* window);
	~InputHandler();

	void setCamera(std::shared_ptr<Camera> cam);
	void setRenderer(std::shared_ptr<Renderer> renderer);
	void setDeltaTime(float deltaTime);

	bool getCameraOn(void) const;
	void setCameraOn(bool cameraOn);
	bool getFirstMouse(void) const;
	bool getTexture(void) const;

	void key_callback(int key, int action);
	void cameraMovement_callback();
	void mouse_callback(double xposIn, double yposIn);

	std::unordered_map<int, std::function<void(int)>> getKeyActions(void) const;

};
#endif 