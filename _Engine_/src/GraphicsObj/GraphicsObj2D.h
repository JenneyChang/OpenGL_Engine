#pragma once
#ifndef GRAPHICSOBJ_2D_H
#define GRAPHICSOBJ_2D_H

#include "MathEngine.h"
#include "GraphicsObj.h"
#include "Mesh.h"
#include "Image.h"

using namespace Azul;

class GraphicsObj2D : public GraphicsObj
{
public:
	GraphicsObj2D() = delete;
	GraphicsObj2D(const GraphicsObj2D&) = delete;
	GraphicsObj2D& operator=(const GraphicsObj2D&) = delete;

	GraphicsObj2D(Mesh* mesh, ShaderObj* shaderobj);
	virtual ~GraphicsObj2D();

	void GetPos(float& x, float& y);


protected:
	Mat4* poMatrix_uv;
	Mat4* poMatrix_orig;

	float origWidth;
	float origHeight;
	float origPosx;
	float origPosy;


};
#endif // !GRAPHICSOBJ_2D_H
