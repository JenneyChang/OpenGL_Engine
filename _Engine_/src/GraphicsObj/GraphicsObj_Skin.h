#pragma once
#ifndef GRAPHICS_OBJ_SKIN_H
#define GRAPHICS_OBJ_SKIN_H

#include "GraphicsObj3D.h"
#include "MathEngine.h"
#include "Mesh.h"
#include "GameObj_Rigid.h"

#include "Texture.h"

using namespace Azul;

class GraphicsObj_Skin : public GraphicsObj3D
{
public:
	GraphicsObj_Skin() = delete;
	GraphicsObj_Skin(const GraphicsObj_Skin&) = delete;
	GraphicsObj_Skin& operator=(const GraphicsObj_Skin&) = delete;

	GraphicsObj_Skin(Mesh* mesh, ShaderObj* shader, Texture* texture, GameObj_Rigid* pivot, 
		Vec4& color, Vec3& pos);
	virtual ~GraphicsObj_Skin();

	void SetSSBOWorldResult(SSBO* pSSBOIn);

	void SetLightColor(Vec4* color);
	void SetLighPosition(Vec3* pos);

	void SetState() override;
	void SetGPUData() override;
	void Draw() override;
	void ResetState() override;


private:
	Vec4* poLightColor;
	Vec3* poLightPos;

	GLuint textureID;
	GameObj_Rigid* pPivot;
	SSBO* pSSBO_WorldResult;


};
#endif // !GRAPHICS_OBJ_SKIN_H
