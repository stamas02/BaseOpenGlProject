// Vertex shader with a model transformation uniform

#version 400
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
out vec4 fcolour;

uniform mat4 worldTransformMatrix;
uniform mat4 worldprojectionMatrix;
uniform mat4 worldrotationMatrix;

void main()
{
	vec4 newpos = worldprojectionMatrix * worldrotationMatrix * worldTransformMatrix  *position;
	gl_Position = newpos;
	
	fcolour = colour;
	//fcolour = position * 2.0 + vec4(0.5, 0.5, 0.5, 1.0);
}