## Game_Engine_OpenGL

## PROJECT STRUCTURE

├── Game_Engine_OpenGL/
├── ├── assets/                      # All non-code assets like shaders, textures
├── │   ├── shaders/
├── │   │   ├── Basic.shader
├── │   │   ├── LightCube.shader
├── │   │   ├── LightningShader.shader
├── │   │   └── Sphere.shader
├── │   ├── textures/
├── │   │   ├── monkey.png
├── │   │   └── pudzilla.png
├── ├── external/                    # External third-party libraries
├── │   ├── glfw/                    # GLFW library
├── │   │   ├── include/
├── │   │   │   ├── glad/
├── │   │   │   │   └── glad.h
├── │   │   │   ├── GLFW/
├── │   │   │   │   ├── glfw3.h
├── │   │   │   │   └── glfw3native.h
├── │   │   │   └── KHR/
├── │   │   │       └── khrplatform.h
├── │   │   └── lib/
├── │   │       └── glfw3.lib
├── │   ├── glm/                     # GLM library 
├── │   │   ├── CMakeLists.txt
├── │   │   └── (GLM source files)
├── │   ├── imgui/                   # ImGui library 
├── │   │   ├── CMakeLists.txt
├── │   │   └── (ImGui source files)
├── │   └── stb_image/               # stb_image library
├── │       ├── stb_image.cpp
├── │       └── stb_image.h
├── ├── GameEngine/                  # Main game engine code
├── │   ├── include/                 # Public headers
├── │   │   ├── IO/
├── │   │   │   └── InputHandler.h
├── │   │   ├── objects/
├── │   │   │   ├── Cube.h
├── │   │   │   ├── Cuboid.h
├── │   │   │   ├── Pyramid.h
├── │   │   │   ├── Solid.h
├── │   │   │   └── Sphere.h
├── │   │   ├── Camera.h
├── │   │   ├── EBO.h
├── │   │   ├── Mesh.h
├── │   │   ├── Renderer.h
├── │   │   ├── Shader.h
├── │   │   ├── Texture.h
├── │   │   ├── VAO.h
├── │   │   └── VBO.h
├── │   ├── src/                     # Source files
├── │   │   ├── IO/
├── │   │   │   └── InputHandler.cpp
├── │   │   ├── objects/
├── │   │   │   ├── Cube.cpp
├── │   │   │   ├── Cuboid.cpp
├── │   │   │   ├── Pyramid.cpp
├── │   │   │   └── Sphere.cpp
├── │   │   ├── Camera.cpp
├── │   │   ├── EBO.cpp
├── │   │   ├── Mesh.cpp
├── │   │   ├── Renderer.cpp
├── │   │   ├── Shader.cpp
├── │   │   ├── Texture.cpp
├── │   │   ├── VAO.cpp
├── │   │   └── VBO.cpp
├── │   └── tests/                   # Test files
├── │       └── (Test-related files)
├── ├── docs/                        # Documentation
├── │   ├── CMakeLists.txt
├── │   └── README.md
├── ├── build/                       # Build folder
├── │   └── (Build files and directories)
├── ├── CMakeLists.txt              
└── └── Readme.md   
