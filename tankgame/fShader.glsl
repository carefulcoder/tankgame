varying vec2 texture_coordinate;
uniform sampler2D texture;
uniform vec4 uvs;

void main(void)
{
	vec2 uv = vec2(uvs[0] + (fract(texture_coordinate.x) * (uvs[2] - uvs[0])), uvs[1] + (fract(texture_coordinate.y) * (uvs[3] - uvs[1])));
	gl_FragColor = texture2D(texture, uv);
}