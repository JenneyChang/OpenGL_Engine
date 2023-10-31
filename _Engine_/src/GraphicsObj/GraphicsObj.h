#pragma once
#ifndef GRAPHICS_OBJ_H
#define GRAPHICS_OBJ_H

#include "Material.h"
#include "MathEngine.h"
#include "BoundingSphere.h"
#include "ShaderObj.h"

using namespace Azul;

class Mesh;

class GraphicsObj : public Material
{
public:
	GraphicsObj() = delete;
	GraphicsObj(const GraphicsObj&) = delete;
	GraphicsObj& operator=(const GraphicsObj&) = delete;

	GraphicsObj(Mesh* mesh, const ShaderObj* pShaderObj);
	virtual ~GraphicsObj();

	virtual void Render() = 0;

	void SetWorldMat(Azul::Mat4& world);
	Azul::Mat4& GetWorldMat();

	Mesh* GetMesh() const;


protected:
	Mesh* pMesh;
	Azul::Mat4* poWorld;
	const ShaderObj* pShaderObj;


};
#endif // !GRAPHICS_OBJ_H
