varying vec2 texture_coordinate;
uniform sampler2D texture;

void main(void)
{
	gl_FragColor = texture2D(texture, texture_coordinate);
}