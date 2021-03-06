#version 330

uniform sampler2D tex;
uniform vec4 customColor;

varying vec2 texCoord;

void main(void)
{
	gl_FragColor = texture2D(tex, texCoord) * customColor;
}
