
// Uniforms
uniform sampler2D tex_object;


// Varying
in VS_OUT
{
	vec2 vTex;
	vec4 vFragColor;
} fs_in;

out vec4 color;

void main(void)
{
   color = fs_in.vFragColor * texture(tex_object, fs_in.vTex);
}
