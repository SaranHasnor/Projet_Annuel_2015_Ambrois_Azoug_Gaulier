
uniform sampler2DRect tex;

void main ()
{
	gl_FragColor = texture(tex, gl_PointCoord);
}
