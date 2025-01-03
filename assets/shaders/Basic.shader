#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_view;

void main()
{
	gl_Position = u_MVP * vec4(position,1.0);
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

out vec4 color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord);
};