#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "factories/MeshFactory.h"
#include "MeshRegistry.h"
#include "objects/Cuboid.h"


class SolidMock : public Solid {
public:
    MOCK_METHOD(void, Initalize, (), (override));
    MOCK_METHOD(void, UpdateVerticesAndIndices, (), (override));
    MOCK_METHOD(void, UpdateParams, (), (override));
};

class FactoriesTest : public ::testing::Test {
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

TEST_F(FactoriesTest, PassingValuesTest) {
	Cuboid cuboid;
    auto vertices = cuboid.GetVertices();
	auto indices = cuboid.GetIndices();
	RenderObject renderObject = RenderObject::Cuboid;
	std::vector<TextureStruct> textures;
    std::vector<std::pair<RenderObject, Solid*>> vecObjects = {
		{renderObject, &cuboid}
    };
	MeshRegistry meshRegistry(vecObjects, textures);
    auto mesh = meshRegistry.GetMeshFromMap(renderObject);
    auto meshVertices = mesh.GetVertices();
	auto meshIndices = mesh.GetIndices();
	ASSERT_EQ(vertices.size(), meshVertices.size());
	ASSERT_EQ(indices.size(), meshIndices.size());
	for (size_t i = 0; i < vertices.size(); i++) {
		ASSERT_EQ(vertices[i].Position, meshVertices[i].Position);
		ASSERT_EQ(vertices[i].Normal, meshVertices[i].Normal);
		ASSERT_EQ(vertices[i].TexCoords, meshVertices[i].TexCoords);
	}
	for (size_t i = 0; i < indices.size(); i++) {
		ASSERT_EQ(indices[i], meshIndices[i]);
	}
}