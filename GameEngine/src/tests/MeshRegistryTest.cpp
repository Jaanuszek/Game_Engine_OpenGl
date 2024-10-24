#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>
#include "MeshRegistry.h"
#include "objects/Torus.h"
#include "objects/Cube.h"
#include "objects/Sphere.h"
#include "objects/Cylinder.h"

std::vector<std::pair<RenderObject, Solid*>> getVecObjects(RenderObject renderObject, Solid* solid) {
	std::vector<std::pair<RenderObject, Solid*>> vecObjects;
	if (renderObject != RenderObject::Assimp) {

		vecObjects.push_back({ renderObject, solid });
	}
	else {

		vecObjects.push_back({ renderObject, nullptr });
	}
	return vecObjects;
}
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
	Torus torus;
	std::vector<std::pair<RenderObject, Solid*>> vecObjects = getVecObjects(renderObject, &torus);
    std::vector<TextureStruct> vecSelectedTexture;
    MeshRegistry meshRegistry(vecObjects, vecSelectedTexture);
    // this should be places in different file
    //EXPECT_TRUE((std::is_base_of<Solid, Torus>::value));
    //Solid* solidPtr = new Cube();
	//EXPECT_NE(dynamic_cast<Cube*>(solidPtr), nullptr);
	EXPECT_EQ(meshRegistry.GetMeshMap().size(), 1);
	EXPECT_EQ(typeid(meshRegistry.GetMeshFromMap(renderObject)), typeid(Mesh));
}

TEST_F(MeshRegistryTest, copyConstructorTest) {
    RenderObject renderObject = RenderObject::Torus;
    Torus torus;
	std::vector<std::pair<RenderObject, Solid*>> vecObjects = getVecObjects(renderObject, &torus);
	MeshRegistry meshRegistry(vecObjects, std::vector<TextureStruct>());
	MeshRegistry meshRegistry1(meshRegistry);
	EXPECT_EQ(meshRegistry.GetMeshMap().size(), meshRegistry1.GetMeshMap().size());
	EXPECT_EQ(meshRegistry1.GetMeshMap().size(), 1);
}

TEST_F(MeshRegistryTest, copyAssignmentTest) {
	RenderObject renderObject = RenderObject::Torus;
	Torus torus;
	std::vector<std::pair<RenderObject, Solid*>> vecObjects = getVecObjects(renderObject, &torus);
	MeshRegistry meshRegistry(vecObjects, std::vector<TextureStruct>());
	MeshRegistry meshRegistry1(vecObjects, std::vector<TextureStruct>());
	meshRegistry1 = meshRegistry;
	EXPECT_EQ(meshRegistry.GetMeshMap().size(), meshRegistry1.GetMeshMap().size());
	EXPECT_EQ(meshRegistry1.GetMeshMap().size(), 1);
	EXPECT_NO_THROW(meshRegistry1.GetMeshFromMap(RenderObject::Torus), std::runtime_error);
	EXPECT_NO_THROW(meshRegistry1.GetFactoryFromMap(RenderObject::Torus), std::runtime_error);
}

TEST_F(MeshRegistryTest, moveConstructorTest) {
	RenderObject renderObject = RenderObject::Torus;
	Torus torus;
	std::vector<std::pair<RenderObject, Solid*>> vecObjects = getVecObjects(renderObject, &torus);
	MeshRegistry meshRegistry(vecObjects, std::vector<TextureStruct>());
	MeshRegistry meshRegistry1(std::move(meshRegistry));
	EXPECT_EQ(meshRegistry.GetMeshMap().size(), 0);
	EXPECT_EQ(meshRegistry1.GetMeshMap().size(), 1);
	MeshRegistry meshRegistry2(std::move(meshRegistry1));
	EXPECT_EQ(meshRegistry1.GetMeshMap().size(), 0);
	EXPECT_EQ(meshRegistry2.GetMeshMap().size(), 1);
}

TEST_F(MeshRegistryTest, moveAssignmentTest) {
	RenderObject renderObject = RenderObject::Cylinder;
	Cylinder cylinder;
	std::vector<std::pair<RenderObject, Solid*>> vecObjects = getVecObjects(renderObject, &cylinder);
	MeshRegistry meshRegistry(vecObjects, std::vector<TextureStruct>());
	MeshRegistry meshRegistry1(vecObjects, std::vector<TextureStruct>());
	meshRegistry1 = std::move(meshRegistry);
	EXPECT_EQ(meshRegistry.GetMeshMap().size(), 0);
	EXPECT_EQ(meshRegistry1.GetMeshMap().size(), 1);
	MeshRegistry meshRegistry2(vecObjects, std::vector<TextureStruct>());
	meshRegistry2 = std::move(meshRegistry1);
	EXPECT_EQ(meshRegistry1.GetMeshMap().size(), 0);
	EXPECT_EQ(meshRegistry2.GetMeshMap().size(), 1);
	EXPECT_THROW(meshRegistry.GetMeshFromMap(RenderObject::Cylinder), std::runtime_error);
	EXPECT_THROW(meshRegistry.GetFactoryFromMap(RenderObject::Cylinder), std::runtime_error);
	EXPECT_NO_THROW(meshRegistry2.GetMeshFromMap(RenderObject::Cylinder), std::runtime_error);
	EXPECT_NO_THROW(meshRegistry2.GetFactoryFromMap(RenderObject::Cylinder), std::runtime_error);
}

TEST_F(MeshRegistryTest, checkingExcpetionsTest) {
	RenderObject renderObject = RenderObject::Assimp;
	Cube cube;
	std::vector<std::pair<RenderObject, Solid*>> vecObjects = getVecObjects(renderObject, &cube);
	EXPECT_THROW(MeshRegistry meshRegistry1(vecObjects, std::vector<TextureStruct>()), std::runtime_error);
	renderObject = RenderObject::Cube;
	vecObjects = getVecObjects(renderObject, nullptr);
	EXPECT_THROW(MeshRegistry meshRegistry2(vecObjects, std::vector<TextureStruct>()), std::runtime_error);
	//EXPECT_THROW(meshRegistry.GetMeshFromMap(RenderObject::Cube), std::runtime_error);
	//EXPECT_THROW(meshRegistry.GetFactoryFromMap(RenderObject::Cube), std::runtime_error);
}