#pragma once
#ifndef GRAPHICS_OBJ_NULL_H
#define GRAPHICS_OBJ_NULL_H

#include "GraphicsObj.h"

class GraphicsObj_Null : public GraphicsObj
{
public:
	GraphicsObj_Null() = delete;
	GraphicsObj_Null(const GraphicsObj_Null&) = delete;
	GraphicsObj_Null& operator=(const GraphicsObj_Null&) = delete;

	GraphicsObj_Null(Mesh* _mesh, const ShaderObj* _shaderObj);
	virtual ~GraphicsObj_Null();

	void Render() override;

	/*void SetState() override;
	void SetGPUData() override;
	void Draw() override;
	void ResetState() override;*/


};
#endif // !GRAPHICS_OBJ_NULL_H
