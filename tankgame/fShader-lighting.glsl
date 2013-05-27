varying vec2 texture_coordinate;
uniform sampler2D texture;

void main(void)
{
	float constant = 1.0f;
	float linear = 0.0014f;
	float quad = 0.00007f;
	
	float length = distance(gl_FragCoord, vec3(400.0f, 200.0f, 5.0f));
	float attenFactor = 1.0f / (constant + (linear * length) + (quad * pow(length, 2.0f)));
	vec4 ambient = vec4(0.2f, 0.2f, 0.2f, 0.0f);
	
	vec4 intensity = vec4(0.8f, 0.8f, 0.8f, 1.0f) * attenFactor;
	intensity.a = 1.0f;

	gl_FragColor = texture2D(texture, texture_coordinate) * (intensity + ambient);
}