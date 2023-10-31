#include "ShaderGraphics.h"

//---------------------------------------------------------------------------
//	CONSTRUCTOR
//---------------------------------------------------------------------------

ShaderGraphics::ShaderGraphics(ShaderObj::Name _name, const char* shaderName)
	: ShaderObj(), fs(0), vs(0)
{ 
	assert(shaderName);
	this->prCreateShader(this->programObj, shaderName);
	this->name = _name;
}

ShaderGraphics::~ShaderGraphics()
{
	this->prClear();
}


//---------------------------------------------------------------------------
//	PROTECTED METHODS
//---------------------------------------------------------------------------

void ShaderGraphics::prClear()
{
	if (this->programObj)
	{
		glUseProgram(0);
		glDeleteProgram(this->programObj);
		glDeleteShader(this->fs);
		glDeleteShader(this->vs);

		this->name = ShaderObj::Name::UNINITIALIZED;
		this->programObj = 0;
		this->fs = 0;
		this->vs = 0;
	}
}

bool ShaderGraphics::prCreateShader(GLuint& _programObj, const char* pShaderFile)
{
	bool status = false;
	char buff[128];

	//fragment shader
	strcpy_s(buff, 128, pShaderFile);
	strcat_s(buff, 128, ".fs");

	//GLuint fs;
	status = prCompileShader(this->fs, buff, GL_FRAGMENT_SHADER);
	assert(status == true);

	//vertex shader
	strcpy_s(buff, 128, pShaderFile);
	strcat_s(buff, 128, ".vs");

	//GLuint vs;
	status = prCompileShader(this->vs, buff, GL_VERTEX_SHADER);
	assert(status == true);

	//create empty program obj
	_programObj = glCreateProgram();

	//attach shader obj --> program obj
	glAttachShader(_programObj, this->vs);
	glAttachShader(_programObj, this->fs);

	//link program obj
	glLinkProgram(_programObj);

	return status;
}

bool ShaderGraphics::prCompileShader(GLuint& shaderObj, const char* pShaderFile, GLenum shaderType)
{
	//load shader file
	char* pBuff_shaderfile = nullptr;
	int buff_shaderfileSize = 0;

	//opengl version
	const char* pVersion = "#version 430 core\n\n";
	size_t versionSize = strlen(pVersion);

	this->prLoadFile(pShaderFile, pBuff_shaderfile, buff_shaderfileSize);
	assert(pBuff_shaderfile);
	assert(buff_shaderfileSize > 0);

	//load ShaderLayout.h
	char* pBuff_ShaderyLayout = nullptr;
	int buff_ShaderyLayoutSize = 0;
	size_t dataSize = 0;
	char* data = nullptr;
	if (shaderType == GL_VERTEX_SHADER)
	{
		this->prLoadFile("ShaderLayout.h", pBuff_ShaderyLayout, buff_ShaderyLayoutSize);
		assert(pBuff_ShaderyLayout);
		assert(buff_ShaderyLayoutSize > 0);

		//total shader filesize + 1 (null term)
		dataSize = versionSize + buff_ShaderyLayoutSize + buff_shaderfileSize + 1;

		//glue shader file in desired layout
		data = new char[dataSize]();
		memset(data, 0, dataSize);

		strcat_s(data, dataSize, pVersion);
		strcat_s(data, dataSize, pBuff_ShaderyLayout);
		strcat_s(data, dataSize, pBuff_shaderfile);
	}
	else
	{
		assert(shaderType == GL_FRAGMENT_SHADER);
		dataSize = versionSize + buff_shaderfileSize + 1;

		//glue shader file together
		data = new char[dataSize]();
		memset(data, 0, dataSize);

		strcat_s(data, dataSize, pVersion);
		strcat_s(data, dataSize, pBuff_shaderfile);
	}

	//create opengl shader obj-------------------------------------------------------

	shaderObj = glCreateShader(shaderType);
	assert(shaderObj);

	glShaderSource(shaderObj, 1, &data, NULL);
	glCompileShader(shaderObj);

	//clean up
	delete[] pBuff_ShaderyLayout;
	delete[] pBuff_shaderfile;
	delete[] data;

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
