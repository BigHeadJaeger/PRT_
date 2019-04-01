#version 430

layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec3 vertexColor;

//uniform mat4 world;
uniform mat4 worldViewProj;

//out	vec3 posW;
out vec3 color;

void main()
{
	gl_Position=worldViewProj*vec4(vertexPosition,1.0);
	color=vertexColor;
}