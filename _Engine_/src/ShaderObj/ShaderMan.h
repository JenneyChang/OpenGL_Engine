#pragma once
#ifndef SHADER_MAN_H
#define SHADER_MAN_H

#include "Manager.h"
#include "ShaderNode.h"
#include "ShaderObj.h"


class ShaderMan : public Manager
{
public:
	ShaderMan(const ShaderMan&) = delete;
	ShaderMan& operator=(const ShaderMan&) = delete;

	static void Create(int toReserve = 3, int toGrow = 1);
	static void Destroy();
	
	static ShaderObj* Add(ShaderObj* shaderobj);
	static ShaderObj* Find(ShaderObj::Name name);
	static void Remove(ShaderObj::Name name);
	static void Print();


protected:
	Node* derivedCreateNode() override;


private:
	ShaderNode* poComparison;
	
	static ShaderMan* poInstance;
	static ShaderMan* prInstance();

	ShaderMan(int toReserve, int toGrow);
	~ShaderMan();
	

};
#endif // !SHADER_MAN_H
