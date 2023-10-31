#pragma once
#ifndef SHADER_OBJ_H
#define SHADER_OBJ_H

#include "sb7.h"

class ShaderObj
{
public:
	enum class Name
	{
		WIREFRAME,

		SPRITE,
		TEXTURE,
		TEXTURE_LIGHT,
		COLOR_LIGHT,

		SKIN_TEXTURE,
		BLINN_PHONG,

		COMPUTE_MIXER,
		COMPUTE_WORLD,

		NULL_SHADER,
		UNINITIALIZED
	};

	ShaderObj(const ShaderObj&) = delete;
	ShaderObj& operator=(const ShaderObj&) = delete;

	ShaderObj();
	virtual ~ShaderObj();

	void Set(ShaderObj::Name _name);
	ShaderObj::Name Get();

	void SetActive() const;
	GLint GetLocation(const char* pUniform) const;


protected:
	ShaderObj::Name name;
	GLuint programObj;

	virtual void prClear() = 0;
	virtual bool prCreateShader(GLuint& programObj, const char* pShaderFile) = 0;
	virtual bool prCompileShader(GLuint& shaderObj, const char* pShaderFile, GLenum shaderType) = 0;
	void prLoadFile(const char* const filename, char*& buff, int& buffsize);


};
#endif // !SHADER_OBJ_H
