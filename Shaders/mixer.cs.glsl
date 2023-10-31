#version 430 core

//local layout 
layout(local_size_x = 10, local_size_y = 1, local_size_z = 1) in;

//match engine 
struct Joint
{
	vec3 t;
	vec4 r;
	vec3 s;
};

//Shader storage buffers
layout (std430, binding = 0) buffer KeyframeA
{
	Joint KeyA[];
};

layout (std430, binding = 1) buffer KeyframeB
{
	Joint KeyB[];
};

layout (std430, binding = 2) buffer KeyResult
{
	Joint Result[];
};

//uniforms
uniform float ts;
uniform int numJoints;

//Function
vec4 slerp( vec4 src, vec4 tar, float t);

void main()
{
	uint jointIndex = gl_GlobalInvocationID.x;

	if(gl_GlobalInvocationID.x < numJoints)
	{
		//Result[jointIndex] = KeyA[jointIndex];

		vec3 trans = mix(KeyA[jointIndex].t, KeyB[jointIndex].t, ts);
		vec4 rot = slerp(KeyA[jointIndex].r, KeyB[jointIndex].r, ts);
		vec3 scale = mix(KeyA[jointIndex].s, KeyB[jointIndex].s, ts);

		Result[jointIndex].t = trans;
		Result[jointIndex].r = rot;
		Result[jointIndex].s = scale;
	}
}

//Function Definition
vec4 slerp( vec4 src, vec4 tar, float t)
{
	float QUAT_EPSILON = 0.001f;

	vec4 result;
	vec4 target;
	
	float cosom = src.x*tar.x + src.y*tar.y + src.z*tar.z + src.w*tar.w;

	if(cosom >= 1.0f)
	{
		// do nothing
		result = src;
	}
	else
	{
		// adjust signs if necessary
		if (cosom < 0.0f)
		{
			cosom = -cosom;
			target = -tar;
		}
		else
		{
			target = tar;
		}

		// If the the source and target are close, we can do a lerp.
		float tarFactor = t;
		float srcFactor = 1.0f - t;

		// calculate coefficients
		if (cosom < (1.0f - QUAT_EPSILON))
		{
			// Quats are not close enough for a lerp.
			// Calculating coefficients for a slerp.
			const float omega = acos(cosom);
			const float sinom = 1.0f / sin(omega);

			srcFactor = sin(srcFactor * omega) * sinom;
			tarFactor = sin(tarFactor * omega) * sinom;
		}

		result.x = src.x * srcFactor + target.x * tarFactor;
		result.y = src.y * srcFactor + target.y * tarFactor;
		result.z = src.z * srcFactor + target.z * tarFactor;
		result.w = src.w * srcFactor + target.w * tarFactor;
	}

	return result;
}
