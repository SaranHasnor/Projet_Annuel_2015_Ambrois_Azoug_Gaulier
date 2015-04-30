
in vec3 pos;
in vec2 texpos;

out vec2 texCoord;

/*
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
*/
void main(void)
{
	//gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);

	texCoord = vec2(0.5, 0.5) + pos.xy;

	// Temporary
	gl_Position = vec4(pos, 1.0);
}
