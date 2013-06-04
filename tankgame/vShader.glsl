varying vec2 texture_coordinate;
uniform mat4 mvp;

void main(void)
{
    gl_Position = mvp * gl_Vertex;
    texture_coordinate = vec2(gl_MultiTexCoord0);
}