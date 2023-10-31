layout(std430, binding = 0) buffer WorldResult
{
	mat4 World[];
};

// Uniforms
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 pivotTRS;

uniform vec4 vColor;
uniform vec3 vLightPos;
uniform vec3 vViewPos;

// Attributes
layout (location = ATTRIB_LOC_VERT) in vec4 vert;
layout (location = ATTRIB_LOC_NORMS) in vec3 norms;
layout (location = ATTRIB_LOC_TEXCOORDS) in vec2 uv;

layout (location = ATTRIB_LOC_WEIGHT) in vec4 weight;
layout (location = ATTRIB_LOC_JOINT) in ivec4 joint;

// Varying
out VS_OUT
{
	vec2 vTex;
	vec4 vFragColor;
} vs_out;

void main(void)
{
	// Remember: We use ROW major, but OpenGL GLSL multiplies in reverse order!
	mat4 skin_matrix = weight.x *  World[joint.x] +
					    weight.y * World[joint.y] +
					    weight.z * World[joint.z] +
					    weight.w * World[joint.w];
	
    gl_Position = proj_matrix * view_matrix * pivotTRS * skin_matrix * vert;    

	//gourand shading
	vec3 pos = vec3(pivotTRS * vert);
	vec3 normal = mat3(transpose(inverse(pivotTRS))) * norms;
	
	float ambientStrength = 0.5f;
	vec4 ambient = ambientStrength * vColor;
	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(vLightPos - pos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec4 diffuse = diff * vColor;
	
	float specStrength = 1.0;
	vec3 viewDir = normalize(vViewPos - pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 35);
	vec4 specular = specStrength * spec * vColor;
	
	//pass values to fragment shader
	vs_out.vTex = uv;
	vs_out.vFragColor = ambient + diffuse + specular;
}