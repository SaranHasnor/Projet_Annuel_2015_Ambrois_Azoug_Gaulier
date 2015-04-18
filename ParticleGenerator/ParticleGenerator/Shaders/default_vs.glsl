
in vec3 vp;
in vec2 texCoord;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec2 texCoordOut;

void main ()
{
	texCoordOut = texCoord;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);
}
