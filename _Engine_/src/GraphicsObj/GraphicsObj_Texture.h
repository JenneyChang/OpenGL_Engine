#pragma once
#ifndef GRAPHICS_OBJ_TEXTURE_H
#define GRAPHICS_OBJ_TEXTURE_H

#include "GraphicsObj3D.h"
#include "Texture.h"
#include "Mesh.h"

using namespace Azul;

class GraphicsObj_Texture : public GraphicsObj3D
{
public:
	GraphicsObj_Texture() = delete;
	GraphicsObj_Texture(const GraphicsObj_Texture&) = delete;
	GraphicsObj_Texture& operator=(const GraphicsObj_Texture&) = delete;

	GraphicsObj_Texture(Mesh* mesh, ShaderObj* shaderobj, Texture* texture);
	virtual ~GraphicsObj_Texture();

	void SetState() override;
	void SetGPUData() override;
	void Draw() override;
	void ResetState() override;


private:
	Texture* pTexture;


};
#endif // !GRAPHICS_OBJ_TEXTURE_H
