#pragma once
#ifndef GRAPHICSOBJ_NULL_3D_H
#define GRAPHICSOBJ_NULL_3D_H

#include "GraphicsObj3D.h"

class GraphicsObj_Null3D : public GraphicsObj3D
{
public:
	GraphicsObj_Null3D() = delete;
	GraphicsObj_Null3D(const GraphicsObj_Null3D&) = delete;
	GraphicsObj_Null3D& operator=(const GraphicsObj_Null3D&) = delete;

	GraphicsObj_Null3D(Mesh* mesh, const ShaderObj* shaderobj);
	virtual ~GraphicsObj_Null3D();

	void Render() override;


};

#endif // !GRAPHICSOBJ_NULL_3D_H
