#version 330

in vec3 pos;
in vec2 texpos;

varying vec2 texCoord;

/*
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
*/
void main(void)
{
	texCoord = texpos;

	// Temporary
	gl_Position = vec4(pos, 1.0);
	
	//gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}
