uniform sampler2D texture;

void main(void)
{
	gl_FragColor = texture2D(texture, vec2(gl_TexCoord[0]));
}