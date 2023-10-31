#pragma once
#ifndef SSBO_H
#define SSBO_H

#include "sb7.h"

//Shader Storage Buffer Object (for Compute Shader)
class SSBO
{
public:
	//TODO: remove after it works
	enum class Access
	{
		READ_ONLY = GL_READ_ONLY,
		WRITE_ONLY = GL_WRITE_ONLY,
		READ_WRITE = GL_READ_WRITE
	};

	SSBO();
	~SSBO();
	SSBO(const SSBO&) = delete;
	SSBO& operator=(const SSBO&) = delete;

	void Set(unsigned int _count, unsigned int _size, void* inbuff);
	void* GetBuffer();

	unsigned int GetLocation() const;
	void Bind(unsigned int loc);

	void* Map(SSBO::Access _access);
	void Unmap();


private:
	GLuint ssbo;
	unsigned int count;
	unsigned int size;
	void* poBuffer;


};
#endif // !SSBO_H
