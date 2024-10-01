#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec3 aNormal;

out vec2 TexCoords;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_view;

void main()
{
	TexCoords = aTexCoords;
	gl_Position = u_MVP * vec4(aPos, 1.0);
};

#shader fragment
#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

void main()
{
	FragColor = texture(texture_diffuse1, TexCoords);
};