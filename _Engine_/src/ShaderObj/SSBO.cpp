#include "SSBO.h"


//---------------------------------------------------------------------------
//	CONSTRUCTION
//---------------------------------------------------------------------------

SSBO::SSBO()
	: ssbo(), count(0), size(0), poBuffer(nullptr)
{
	//create ssbo
	glGenBuffers(1, &ssbo);
}

SSBO::~SSBO()
{
	//tell GPU release it
	glDeleteBuffers(1, &ssbo);

	this->poBuffer = nullptr;
}


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void SSBO::Set(unsigned int _count, unsigned int _size, void* inbuff)
{
	this->count = _count;
	this->size = _size;
	this->poBuffer = inbuff;

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)(count * size), this->poBuffer, GL_STATIC_DRAW);
}

void* SSBO::GetBuffer()
{
	assert(poBuffer);
	return this->poBuffer;
}

unsigned int SSBO::GetLocation() const
{
	return this->ssbo;
}

void SSBO::Bind(unsigned int loc)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, loc, this->ssbo);
}

void* SSBO::Map(SSBO::Access _access)
{
	void* result = glMapNamedBuffer(this->ssbo, GLenum(_access));
	assert(result);

	return result;
}

void SSBO::Unmap()
{
	glUnmapNamedBuffer(this->ssbo);
}