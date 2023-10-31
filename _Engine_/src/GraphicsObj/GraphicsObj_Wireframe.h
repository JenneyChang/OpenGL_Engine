#pragma once
#ifndef GRAPHICS_OBJ_WIREFRAME_H
#define GRAPHICS_OBJ_WIREFRAME_H

#include "GraphicsObj3D.h"
#include "MathEngine.h"
#include "Mesh.h"

using namespace Azul;

class GraphicsObj_Wireframe : public GraphicsObj3D
{
public:
	GraphicsObj_Wireframe() = delete;
	GraphicsObj_Wireframe(const GraphicsObj_Wireframe&) = delete;
	GraphicsObj_Wireframe& operator=(const GraphicsObj_Wireframe&) = delete;

	GraphicsObj_Wireframe( Mesh* mesh, const ShaderObj* shaderobj, const Vec4& wirecolor);
	virtual ~GraphicsObj_Wireframe();

	void SetColor(const Vec4& color);

	void SetState()override;
	void SetGPUData() override;
	void Draw() override;
	void ResetState() override;


private:
	Vec4* poWirecolor;


};
#endif // !GRAPHICS_OBJ_WIREFRAME_H
