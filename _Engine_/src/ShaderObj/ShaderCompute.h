#pragma once
#ifndef SHADER_COMPUTE_H
#define SHADER_COMPUTE_H

#include "ShaderObj.h"

class ShaderCompute : public ShaderObj
{
public:
	ShaderCompute(const ShaderCompute&) = delete;
	ShaderCompute& operator=(const ShaderCompute&) = delete;

	ShaderCompute(ShaderObj::Name _name, const char* shaderName);
	virtual ~ShaderCompute();

	//group size x, y, z
	void Dispatch(unsigned int x, unsigned int y, unsigned int z);


protected:
	GLuint cs;

	void prClear() override;
	bool prCreateShader(GLuint& programObj, const char* pShaderFile) override;
	bool prCompileShader(GLuint& shaderObj, const char* pShaderFile, GLenum shaderType) override;


};
#endif // !SHADER_COMPUTE_H
