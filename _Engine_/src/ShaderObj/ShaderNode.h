#pragma once
#ifndef SHADER_NODE_H
#define SHADER_NODE_H

#include "DLink.h"
#include "ShaderObj.h"

class ShaderNode : public DLink
{
public:
	ShaderNode(const ShaderNode&) = delete;
	ShaderNode& operator=(const ShaderNode&) = delete;

	ShaderNode();
	virtual ~ShaderNode();

	void Set( ShaderObj* shaderobj);
	ShaderObj* Get();

	bool Compare(Node* pNode) override;


private:
	ShaderObj* poShaderObj;


};
#endif // !SHADER_NODE_H
