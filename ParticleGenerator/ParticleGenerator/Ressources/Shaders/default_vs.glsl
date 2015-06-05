#version 330

in vec3 pos;
in vec2 texpos;

varying vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix; // Premultiplied view and projection matrix

void main(void)
{
	texCoord = texpos;

	gl_Position = viewMatrix * modelMatrix * vec4(pos, 1.0);
}
