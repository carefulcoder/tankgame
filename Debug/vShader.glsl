varying vec2 texture_coordinate;
uniform mat4 mvp;
uniform vec2 uvs;

void main(void)
{
	if (gl_MultiTexCoord0.x == 0) {
		gl_MultiTexCoord0.x = uvs[0];
	} else {
		gl_MultiTexCoord0.x = uvs[2];
	}
	
	if (gl_MultiTexCoord0.y == 0) {
		gl_MultiTexCoord0.y = uvs[1];
	} else {
		gl_MultiTexCoord0.y = uvs[3];
	}

    gl_Position = mvp * gl_Vertex;
    texture_coordinate = vec2(gl_MultiTexCoord0);
}