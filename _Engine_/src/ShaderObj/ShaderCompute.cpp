#include "ShaderCompute.h"

//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

ShaderCompute::ShaderCompute(ShaderObj::Name _name, const char* shaderName)
	: ShaderObj(), cs(0)
{
	assert(shaderName);
	this->prCreateShader(this->programObj, shaderName);
	this->name = _name;
}

ShaderCompute::~ShaderCompute()
{
	this->prClear();
}


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void ShaderCompute::Dispatch(unsigned int x, unsigned int y, unsigned int z)
{
	glDispatchCompute(x, y, z);
}


//---------------------------------------------------------------------------
//	PROTECTED METHODS
//---------------------------------------------------------------------------

void ShaderCompute::prClear()
{
	if (this->programObj)
	{
		glUseProgram(0);
		glDeleteProgram(this->programObj);
		glDeleteShader(this->cs);

		this->name = ShaderObj::Name::UNINITIALIZED;
		this->programObj = 0;
		this->cs = 0;
	}
}

bool ShaderCompute::prCreateShader(GLuint& _programObj, const char* pShaderFile)
{
	assert(pShaderFile);

	bool status = false;
	char buff[128];

	strcpy_s(buff, 128, pShaderFile);
	strcat_s(buff, 128, ".cs.glsl");

	status = this->prCompileShader(this->cs, buff, GL_COMPUTE_SHADER);
	assert(status == true);

	// Creates an empty program object
	_programObj = glCreateProgram();

	//Attaches a shader object to a program object
	glAttachShader(_programObj, cs);

	// Links a program object
	glLinkProgram(_programObj);

	return status;
}

bool ShaderCompute::prCompileShader(GLuint& shaderObj, const char* pShaderFile, GLenum shaderType)
{
	assert(shaderType == GL_COMPUTE_SHADER);
	char* pBuffer = nullptr;
	int fileSize = 0;

	//load shader file
	this->prLoadFile(pShaderFile, pBuffer, fileSize);
	assert(pBuffer);
	assert(fileSize > 0);

	//add null terminator
	pBuffer[fileSize] = 0;

	//create and load shader obj
	shaderObj = glCreateShader(shaderType);
	assert(shaderObj);

	glShaderSource(shaderObj, 1, &pBuffer, NULL);
	glCompileShader(shaderObj);

	delete[] pBuffer;

	//check for errors
	GLint status = 0;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		char buffer[4096];
		glGetShaderInfoLog(shaderObj, 4096, NULL, buffer);

		Trace::out("Error(ShaderCompile.cpp) %s: %s\n", pShaderFile, buffer);

		glDeleteShader(shaderObj);

		assert(false);
		return false;
	}
	else
	{
		return true;
	}
}
