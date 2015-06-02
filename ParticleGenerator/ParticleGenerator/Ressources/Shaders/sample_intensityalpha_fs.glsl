#version 330

uniform sampler2D tex;

varying vec2 texCoord;

void main(void)
{
	vec3 inColor = texture2D(tex, texCoord).rgb;
	float intensity = (inColor.r + inColor.g + inColor.b) / 3.0;
	gl_FragColor = vec4(inColor, intensity);
}
