# Game Engine OpenGL TODO CHANGE NAME!!

## DESCRIPTION
TODO: create and change the name of project<br>
<name_of_project> is a simple game engine that renders some basic 3D objects. 
Using a GUI you can generate various 3D objects, execute transformation (such as rotating, translating, scaling), apply shaders and place custom textures. 
User can move around the scene using a camera and change the view with the mouse. 
There is also straightforward light physics (one source of light that affects the objects). 
The project is written in C++ and uses OpenGL, and other external libraries that are described [here](#external-libraries).<br>
This is also my bachelor's thesis project.
## INSTALLATION
   
### Prerequisites
- CMake
- C++ compiler
- OpenGL
- GLFW
- On Windows: Visual Studio 17
- On Linux: TODO
- On MacOS: TODO

### Build on windows
1. Clone the repository
2. Open the project in Visual Studio 17<br>
![Open project](../readme_dependencies/running_vs.png)
	- Wait a little bit to let cmake generate the project
	- (optional) go to CMakeLists.txt in main directory and use CTRL + S to make sure that the project is generated
3. Build and run the project (F5)<br>

	**In case of some artifacts:**
	- Make sure your PC is running this program with dedicated graphics card.
	- After building the project, check if in your directory is .exe file.
		* If no check if cmake is generated without any errors
	- Go to Settings -> System -> Display -> Graphics
		- In "Custom options for apps" browse and search for Game_Engine.exe
		- Set option High Performance
	![Force graphic card](../readme_dependencies/forcing_dedicated_graphic_card.png)

### Build on Linux
TODO

### Build on MacOS
TODO

## INSTRUCTION
After runing the program there will be GUI with buttons that generates 3D objects.
Some objects have option to dynamically change their values (f.e. Cylinder).
If there are artifacts wile changing objects parameters go here (TODO add link to forcing running program on dedicated graphic card) for quick fix.
In order to use translation on object, use sliders that are below rendering buttons.

### Keybinds
- T - Change objects shader (lightning shader, texture shader)
- C - Toggle camera mode. In this mode user can move around the scene.
- L - Toggle object's mesh
- P - Toggle object's vertices points

## EXTERNAL LIBRARIES

| Library | Description | Link |
| --- | --- | --- |
| GLAD | OpenGL loader | [GLAD](https://glad.dav1d.de/) |
| GLFW | Windowing library | [GLFW](https://www.glfw.org/) |
| GLM | Math library | [GLM](https://glm.g-truc.net/0.9.9/index.html) |
| STB | Image loading library | [STB](https://github.com/nothings/stb/blob/master/stb_image.h)|
| IMGUI | GUI library | [IMGUI](https://github.com/ocornut/imgui)|
| ASSIMP | Model loading library | [ASSIMP](https://www.assimp.org/) |

## LICENSE
