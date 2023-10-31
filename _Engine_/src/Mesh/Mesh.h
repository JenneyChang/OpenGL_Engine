#pragma once
#ifndef MESH_H
#define MESH_H

#include "sb7.h"
#include "MathEngine.h"
#include "BoundingSphere.h"
#include "SSBO.h"

using namespace Azul;

class Mesh
{
public:
	enum class Name
	{
		CUBE,
		PYRAMID,
		SPHERE,

		CRATE,
		FRIGATE,
		R2D2,
		DUCK,
		WATCH_TOWER,
		BARRAMUNDI_FISH,
		CORSET,
		SNOWMAN,
		BUGGY,
		AVOCADO,
		DOGE,
		LORD_SHIVA,
		SNEAKER,

		CHICKEN_BOT,
		MOUSEY,

		SPRITE,

		CAMERA,

		ANTIQUE_CAMERA,
		TIEFIGHTER,

		NULL_MESH,
		UNINITIALIZED
	};

	struct Vertices
	{
		float x;
		float y;
		float z;
	};

	struct Normals
	{
		float nx;
		float ny;
		float nz;
	};

	struct TexCoords
	{
		float u;
		float v;
	};

	struct Indices
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};

	struct Weights
	{
		float wa;
		float wb;
		float wc;
		float wd;
	};

	struct Joints
	{
		unsigned int ja;
		unsigned int jb;
		unsigned int jc;
		unsigned int jd;
	};


	Mesh();
	virtual ~Mesh();
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	void SetName(Mesh::Name _name);
	Mesh::Name GetName();

	int GetTris();
	GLuint GetVAO();
	SSBO* GetSSBOInvbind();
	BoundingSphere* GetSphere();

	Vec4* GetBaseColor();


protected:
	Mesh::Name name;
	BoundingSphere* poSphere;	//TODO: not needed for sprite mesh

	int numVerts;
	int numTris;

	GLuint vao;				//vertex array object
	GLuint vbo_verts;		//vertex buffer object
	GLuint vbo_norms;
	GLuint vbo_texcoords;
	GLuint vbo_color;
	GLuint vbo_index;		//changed-->proto layout

	GLuint vbo_weights;
	GLuint vbo_joints;
	
	SSBO* poSSBO_InvBind;

	Vec4* basecolor;


};
#endif // !MESH_H
