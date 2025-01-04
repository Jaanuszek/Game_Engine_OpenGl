#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Calculations {
public:
	static glm::mat4 CalculateProjectionMatrix(const float& width, const float& height);
	static glm::mat4 CalculateProjectionMatrix(const int& width, const int& height);
	static glm::mat4 CalculateViewMatrix(const glm::vec3& viewTranslation);
	static glm::mat4 CalculateModelMatrix(const float& angle, const glm::vec3& axis, const glm::vec3& translation, const glm::vec3& scale);
	static glm::mat4 CalculateModelMatrix(const glm::vec3& translation);
	static glm::mat4 CalculateMVPMatrix(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model);

	static glm::vec3 CalculateRotation(const glm::vec3& rotation, const glm::vec3& axis);
	static glm::vec3 CalculateTranslation(const glm::vec3& translation, const glm::vec3& direction);
};

#endif