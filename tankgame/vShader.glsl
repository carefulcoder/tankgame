varying vec2 texture_coordinate;
uniform float numSprites;
uniform float spriteNo;
uniform mat4 mvp;

void main(void)
{
	float off = 1.0 / (numSprites);
	gl_MultiTexCoord0.x = (gl_MultiTexCoord0.x * off) + (spriteNo * off);
	
    gl_Position = mvp * gl_Vertex;
    texture_coordinate = vec2(gl_MultiTexCoord0);
}