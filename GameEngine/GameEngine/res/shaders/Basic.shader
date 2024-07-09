#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 color;

out vec2 v_TexCoord;
out vec3 v_Color;

uniform mat4 u_MVP;
//uniform mat4 u_camMatrix;

void main()
{
	gl_Position = u_MVP * vec4(position,1.0);
	v_TexCoord = texCoord;
	v_Color = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; //to i to dziala
//out vec4 color;
in vec2 v_TexCoord;
in vec3 v_Color;

//uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
	//color = vec4(v_Color, 1.0);
};