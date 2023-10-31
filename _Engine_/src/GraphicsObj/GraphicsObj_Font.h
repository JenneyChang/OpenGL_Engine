#pragma once
#ifndef GRAPHICS_OBJ_FONT_H
#define GRAPHICS_OBJ_FONT_H

#include "GraphicsObj2D.h"
#include "MathEngine.h"
#include "Font.h"

class Font;

using namespace Azul;

class GraphicsObj_Font : public GraphicsObj2D
{
public:
	GraphicsObj_Font() = delete;
	GraphicsObj_Font(const GraphicsObj_Font&) = delete;
	GraphicsObj_Font& operator=(const GraphicsObj_Font&) = delete;

	GraphicsObj_Font(Mesh* mesh, ShaderObj* shaderobj);
	virtual ~GraphicsObj_Font();

	void Set(Glyph::Name _glyph, std::string mssg, float _x, float _y);
	void UpdateMessage(std::string mssg);

	void Render() override;


private:
	Glyph* pGlyph;
	Rect* poRect;
	std::string message;

	float x;	//pos
	float y;

	GLuint texID;



};
#endif // !GRAPHICS_OBJ_FONT_H
