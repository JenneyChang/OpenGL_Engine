// TEXTURE RENDER - Vertex Shader

// Uniforms
uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

// Attributes
layout (location = ATTRIB_LOC_VERT) in vec4 position;
layout (location = ATTRIB_LOC_TEXCOORDS) in vec2 tc;

// Varying
out VS_OUT
{
    vec2 textCoordinate;
} vs_out;

void main(void)
{
    vs_out.textCoordinate = tc;
    gl_Position = proj_matrix * view_matrix * world_matrix * position;
}

// --- End of File ---

