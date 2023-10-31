//Sprite shader vertex

layout (location = ATTRIB_LOC_VERT) in vec4 position;
layout (location = ATTRIB_LOC_TEXCOORDS) in vec2 tc;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 uv_matrix;
          
             
out VS_OUT
{
    vec2 textCoordinate;
	mat4 uv_mat;
} vs_out;

void main(void)
{
	// squirrel away the texture and the uv matrix to the fragment stage
    vs_out.textCoordinate = tc;
	vs_out.uv_mat = uv_matrix;

	// create the transformed vert
    gl_Position = proj_matrix * view_matrix * world_matrix * position;
	
}

