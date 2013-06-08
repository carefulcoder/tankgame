varying vec2 texture_coordinate;
varying vec2 actual_tex_coord;
uniform vec2 uvScale;
uniform mat4 mvp;

void main(void)
{
    gl_Position = mvp * gl_Vertex;
    texture_coordinate = vec2(gl_MultiTexCoord0);
	texture_coordinate.x *= uvScale.x;
	texture_coordinate.y *= uvScale.y;
}