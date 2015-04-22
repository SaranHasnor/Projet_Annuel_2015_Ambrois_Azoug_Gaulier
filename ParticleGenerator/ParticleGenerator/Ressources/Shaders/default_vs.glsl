
in vec3 pos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main ()
{
	//gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);

	// Temporary
	gl_Position = vec4(pos, 1.0);
}
