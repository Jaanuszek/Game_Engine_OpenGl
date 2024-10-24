#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "factories/MeshFactory.h"
#include "factories/ObjectFactory.h"
#include "objects/Torus.h"

class SolidMock : public Solid {
public:
    MOCK_METHOD(void, Initalize, (), (override));
    MOCK_METHOD(void, UpdateVerticesAndIndices, (), (override));
	MOCK_METHOD(void, UpdateParams, (), (override));
};

class ObjectFactoryTest : public ::testing::Test {
protected:
    GLFWwindow* window;
	SolidMock solid;
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

TEST_F(ObjectFactoryTest, CreateMesh) {
	RenderObject renderObject = RenderObject::Torus;
	Torus torus;
	std::unique_ptr<IObjectFactory> factory = ObjectFactory::GetFactory(renderObject, torus);
	std::vector<TextureStruct> vecSelectedTexture;
	std::shared_ptr<Mesh> mesh = factory->CreateMesh(vecSelectedTexture);
	ASSERT_TRUE(mesh != nullptr);
}

TEST_F(ObjectFactoryTest, GetFactory) {
	RenderObject renderObject = RenderObject::Assimp;
	Torus torus;
	std::unique_ptr<IObjectFactory> factory = ObjectFactory::GetFactory(renderObject, torus);
	ASSERT_TRUE(factory == nullptr);
	renderObject = RenderObject::Torus;
	factory = ObjectFactory::GetFactory(renderObject, torus);
	ASSERT_TRUE(factory != nullptr);
}

TEST_F(ObjectFactoryTest, GetSolidObject) {
	RenderObject renderObject = RenderObject::Torus;
	Torus torus;
	std::unique_ptr<IObjectFactory> factory = ObjectFactory::GetFactory(renderObject, torus);
	Solid& solid = factory->GetSolidObject();
	ASSERT_TRUE(&solid == &torus);
}

TEST_F(ObjectFactoryTest, GetFactoryWithStrangeSolidObject) {
	SolidMock solid;
	//EXPECT_CALL(solid, Initalize())
 //       .Times(1);
 //   solid.Initalize();
	RenderObject renderObject = RenderObject::Cube;
	EXPECT_THROW(std::unique_ptr<IObjectFactory> factory = ObjectFactory::GetFactory(renderObject, solid), std::bad_cast);
}