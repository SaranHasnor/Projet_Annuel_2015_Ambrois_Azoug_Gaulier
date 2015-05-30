#version 330

in vec3 pos;
in vec2 texpos;

varying vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main(void)
{
	texCoord = texpos;

	// Temporary
	gl_Position = modelMatrix * vec4(pos, 1.0);
	
	//gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}
