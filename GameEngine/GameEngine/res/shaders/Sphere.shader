#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 color;
layout(location = 3) in vec3 normal;

out vec3 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position,1.0);
	v_Color = color;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; //to i to dziala

in vec2 v_TexCoord;
in vec3 v_Color;

uniform sampler2D diffuse0;
//uniform vec4 u_Color;

void main()
{
	//color = vec4(v_Color, 1.0);
	vec4 texColor = texture(diffuse0, v_TexCoord);
	color = texColor;
	//color = texColor * vec4(v_Color,1.0);
};