#pragma once
#ifndef SHADER_GRAPHICS_H
#define SHADER_GRAPHICS_H

#include "ShaderObj.h"

class ShaderGraphics : public ShaderObj
{
public:
	ShaderGraphics(const ShaderGraphics&) = delete;
	ShaderGraphics& operator=(const ShaderGraphics&) = delete;

	ShaderGraphics(ShaderObj::Name _name, const char* shaderName);
	virtual ~ShaderGraphics();


protected:
	GLuint fs;
	GLuint vs;
	
	void prClear() override;
	bool prCreateShader(GLuint& programObj, const char* pShaderFile) override;
	bool prCompileShader(GLuint& shaderObj, const char* pShaderFile, GLenum shaderType) override;


};
#endif // !SHADER_GRAPHICS_H
