// TEXTURE RENDER - Fragment Shader

// Uniform
uniform sampler2D tex_object;

// Varying
in VS_OUT
{
    vec2 textCoordinate;
} fs_in;

out vec4 color;

void main(void)
{
    color = texture(tex_object, fs_in.textCoordinate );
}

// --- End of File ---

