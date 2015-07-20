#version 330

uniform sampler2D tex;
uniform vec4 customColor;

varying vec2 texCoord;

void main(void)
{
	vec3 inColor = texture2D(tex, texCoord).rgb * customColor.rgb * customColor.a;
	float intensity = (inColor.r + inColor.g + inColor.b) / 3.0;
	gl_FragColor = vec4(inColor, intensity);
}
