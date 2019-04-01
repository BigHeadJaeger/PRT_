#version 430

in vec3 color;

out vec4 FragColor;

void main()
{
	vec3 result;
	result=color/(vec3(1.0)+color);
	result=pow(result,vec3(1.0/2.2));

	FragColor=vec4(result,1.0);
	//FragColor=vec4(0.5,0.3,0.6,1.0);
	//FragColor=vec4(color,1.0);
}
