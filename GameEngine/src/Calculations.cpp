#include "Calculations.h"

glm::mat4 Calculations::CalculateProjectionMatrix(const float& width, const float& height) {
	return glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
}

glm::mat4 Calculations::CalculateViewMatrix(const glm::vec3& viewTranslation) {
	return glm::translate(glm::mat4(1.0f), viewTranslation);
}

glm::mat4 Calculations::CalculateModelMatrix(const float& angle, const glm::vec3& axis, const glm::vec3 translation) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, translation);
	model = glm::rotate(model, glm::radians(angle), axis);
	return model;
}

glm::mat4 Calculations::CalculateModelMatrix(const glm::vec3& translation) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, translation);
	return model;
}

glm::mat4 Calculations::CalculateMVPMatrix(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model) {
	return projection * view * model;
}

glm::vec3 Calculations::CalculateRotation(const glm::vec3& rotation, const glm::vec3& axis) {
	return rotation + axis;
}

glm::vec3 Calculations::CalculateTranslation(const glm::vec3& translation, const glm::vec3& direction) {
	return translation + direction;
}