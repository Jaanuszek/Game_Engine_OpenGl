#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>
#include "ModelManager.h"

int GetNumberOfDirectories(const std::string& path) {
	int count = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (entry.exists() && entry.is_directory()) {
			count++;
		}
	}
	return count;
}

class SolidMock : public Solid {
public:
    MOCK_METHOD(void, Initalize, (), (override));
    MOCK_METHOD(void, UpdateVerticesAndIndices, (), (override));
    MOCK_METHOD(void, UpdateParams, (), (override));
};

class ManagerTest : public ::testing::Test {
protected:
    GLFWwindow* window;
    //SolidMock solid;
    void SetUp() override {
        // Had to do this because I am getting excpetion when I run the test
        // This code set a valid OpenGL context for the test
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
    }

    void TearDown() override {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

TEST_F(ManagerTest, ModelManagerConstructorTest) {
	std::string path = "resources/objects/nanosuit/nanosuit.obj";
	std::shared_ptr<Model> model;
	EXPECT_THROW(ModelManager modelManager(path,model), std::runtime_error);
	path = "../../../../../assets/models";
	//EXPECT_NO_THROW(ModelManager modelManager1(path));
    ModelManager modelManager1(path, model);
	int directoryCount = GetNumberOfDirectories(path);
	EXPECT_EQ(modelManager1.GetModelsMap().size(), directoryCount);
}

TEST_F(ManagerTest, GetModelFromPathTest) {
	std::string path = "../../../../../assets/models";
    std::shared_ptr<Model> model;
	ModelManager modelManager(path, model);
    auto modelFromPath = modelManager.GetModelFromPath("../../../../../assets/models/monkeyHead/monkeyHead.obj");
	EXPECT_TRUE(modelFromPath != nullptr);
}
