
in vec2 texCoordOut;
uniform sampler2DRect tex;

out vec4 outColor;

void main ()
{
	outColor = texture(tex, texCoordOut);
}
