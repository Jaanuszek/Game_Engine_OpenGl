#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>
#include "MeshRegistry.h"
#include "objects/Torus.h"
#include "objects/Cube.h"

class MeshRegistryTest : public ::testing::Test {
protected:
    GLFWwindow* window;

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

TEST_F(MeshRegistryTest, CrateAndAddMeshToMap) {
	RenderObject renderObject = RenderObject::Torus;
	RenderObject renderObject1 = RenderObject::Cube;
	Torus torus;
	Cube cube;
	std::vector<std::pair<RenderObject, Solid*>> vecObjects{
		{renderObject, &torus}
	};
    std::vector<std::pair<RenderObject, Solid*>> vecObjects1{
        {renderObject1, &cube}
    };
    std::vector<TextureStruct> vecSelectedTexture;
    MeshRegistry meshRegistry(vecObjects, vecSelectedTexture);
	MeshRegistry meshRegistry1(vecObjects1, vecSelectedTexture);
    // this should be places in different file
    //EXPECT_TRUE((std::is_base_of<Solid, Torus>::value));
    //Solid* solidPtr = new Cube();
	//EXPECT_NE(dynamic_cast<Cube*>(solidPtr), nullptr);
	EXPECT_EQ(meshRegistry.GetMeshMap().size(), 1);
	EXPECT_EQ(typeid(meshRegistry.GetMeshFromMap(renderObject)), typeid(Mesh));
	EXPECT_THROW(meshRegistry.GetMeshFromMap(RenderObject::Cube), std::runtime_error);
	EXPECT_THROW(meshRegistry.GetFactoryFromMap(RenderObject::Cuboid), std::runtime_error);
	EXPECT_NE(meshRegistry.GetFactoryFromMap(renderObject), nullptr);
    meshRegistry = meshRegistry1;
    EXPECT_NO_THROW(meshRegistry.GetMeshFromMap(RenderObject::Cube), std::runtime_error);
}