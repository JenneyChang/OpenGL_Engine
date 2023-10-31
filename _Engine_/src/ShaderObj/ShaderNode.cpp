#include "ShaderNode.h"

//---------------------------------------------------------------------------
//	CONSTRUCTOR
//---------------------------------------------------------------------------

ShaderNode::ShaderNode()
	: DLink(), poShaderObj(nullptr)
{ }

ShaderNode::~ShaderNode()
{
	delete this->poShaderObj;
}


//---------------------------------------------------------------------------
//	PUBLIC METHODS
//---------------------------------------------------------------------------

void ShaderNode::Set(ShaderObj* shaderobj)
{
	assert(shaderobj != nullptr);

	this->poShaderObj = shaderobj;
}

ShaderObj* ShaderNode::Get()
{
	assert(poShaderObj);
	return this->poShaderObj;
}


//---------------------------------------------------------------------------
//	OVERRIDDEN METHODS
//---------------------------------------------------------------------------

bool ShaderNode::Compare(Node* pNode)
{
	assert(pNode);
	ShaderNode* pTemp = (ShaderNode*)pNode;
	ShaderObj* pObj = pTemp->Get();

	if (this->poShaderObj->Get() == pObj->Get())
	{
		return true;
	}
	
	return false;
}
