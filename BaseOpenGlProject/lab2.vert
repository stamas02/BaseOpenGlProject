// Vertex shader with a model transformation uniform

#version 400
layout(location = 0) in vec4 position;

out vec4 fcolour;

uniform mat4 worldTransformMatrix;
uniform mat4 worldProjectionMatrix;
uniform mat4 worldRotationMatrix;

uniform mat4 modelMatrix;

void main()
{
	vec4 local_new_pos =  modelMatrix * position;
	vec4 world_new_pos = worldProjectionMatrix * worldRotationMatrix * worldTransformMatrix  * local_new_pos;

	gl_Position = world_new_pos;
	
	fcolour = vec4(0.3f,0.3f,0.3f,1.0f);
	//fcolour = position * 2.0 + vec4(0.5, 0.5, 0.5, 1.0);
}