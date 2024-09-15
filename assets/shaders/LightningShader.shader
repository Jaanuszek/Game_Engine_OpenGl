#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_view;


void main()
{
	gl_Position = u_MVP * vec4(position,1.0);
	v_FragPos = vec3(u_model*vec4(position, 1.0));
	//inversing matrices is a costly operation, better to do it using cpu
	v_Normal = mat3(transpose(inverse(u_model)))*normal;
};

#shader fragment
#version 330 core

out vec4 v_Color;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform sampler2D diffuse0;
uniform vec3 u_objectColor;
uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_lightColor;

	vec3 norm = normalize(v_Normal); //it has to be normalized
	vec3 lightDir = normalize(u_lightPos - v_FragPos);
	float diffuse = max(dot(norm, lightDir), 0.0);

	float specularStrength = 0.5f;
	vec3 viewDir = normalize(u_viewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * u_lightColor;

	vec3 result = (ambient + diffuse + specular) * u_objectColor;

	v_Color = vec4(result,1.0);
};