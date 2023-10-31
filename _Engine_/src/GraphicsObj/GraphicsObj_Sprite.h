#pragma once
#ifndef GRAPHICS_OBJ_SPRITE_H
#define GRAPHICS_OBJ_SPRITE_H

#include "GraphicsObj2D.h"
#include "MathEngine.h"
#include "Mesh.h"
#include "Image.h"

using namespace Azul;

class GraphicsObj_Sprite : public GraphicsObj2D
{
public:
	GraphicsObj_Sprite() = delete;
	GraphicsObj_Sprite(const GraphicsObj_Sprite&) = delete;
	GraphicsObj_Sprite& operator=(const GraphicsObj_Sprite&) = delete;

	GraphicsObj_Sprite(Mesh* mesh, ShaderObj* shaderobj, Image* img, Rect rect);
	virtual ~GraphicsObj_Sprite();

	void SwapImage(Image* img);

	void Render() override;


private:
	Image* pImage;
	GLuint texID;

	void SetState() override;
	void SetGPUData() override;
	void Draw() override;
	void ResetState() override;


};
#endif // !GRAPHICS_OBJ_SPRITE_H
