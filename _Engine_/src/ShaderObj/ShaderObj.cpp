#include "ShaderObj.h"
#include "File.h"

using namespace Azul;

//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

ShaderObj::ShaderObj()
	: name(ShaderObj::Name::UNINITIALIZED), programObj(0)
{  }

ShaderObj::~ShaderObj()
{ }


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void ShaderObj::Set(ShaderObj::Name _name)
{
	this->name = _name;
}

ShaderObj::Name ShaderObj::Get()
{
	return this->name;
}

void ShaderObj::SetActive() const
{
	glUseProgram(this->programObj);
}

GLint ShaderObj::GetLocation(const char* pUniform) const
{
	assert(pUniform);

	GLint location = glGetUniformLocation(this->programObj, pUniform);
	assert(location != -1);

	return location;
}


//---------------------------------------------------------------------------
//	PRIVATE METHODS
//---------------------------------------------------------------------------

void ShaderObj::prLoadFile(const char* const filename, char*& buff, int& buffsize)
{
	File::Handle fh;
	File::Error fstatus;

	std::string path = "Shaders\\" + std::string(filename);

	//open shader for read
	fstatus = File::Open(fh, path.c_str(), File::Mode::READ);
	assert(fstatus == File::Error::SUCCESS);

	//seek to end
	fstatus = File::Seek(fh, File::Position::END, 0);
	assert(fstatus == File::Error::SUCCESS);

	//shader size
	DWORD fileSize;
	fstatus = File::Tell(fh, fileSize);
	assert(fstatus == File::Error::SUCCESS);

	//back to beg & read
	fstatus = File::Seek(fh, File::Position::BEGIN, 0);
	assert(fstatus == File::Error::SUCCESS);

	char* data = new char[fileSize + 1];

	fstatus = File::Read(fh, data, fileSize);
	assert(fstatus == File::Error::SUCCESS);

	//add null termination
	data[fileSize] = 0;

	//close file
	fstatus = File::Close(fh);
	assert(fstatus == File::Error::SUCCESS);

	buff = data;
	buffsize = (int)fileSize;
}