#version 330

in vec3 pos;
in vec2 texpos;

varying vec2 texCoord;

uniform vec3 particlePos;
uniform float particleAngle;

uniform mat4 viewMatrix; // Premultiplied view and projection matrix

void main(void)
{
	texCoord = texpos;

	gl_Position = vec4(particlePos, 1.0) * viewMatrix + vec4(pos, 1.0);
}
