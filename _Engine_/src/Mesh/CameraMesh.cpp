#include "CameraMesh.h"
#include "Camera3DMan.h"
#include "ShaderLayout.h"


//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

CameraMesh::CameraMesh() : Mesh()
{
	this->prCreateMesh();
}

CameraMesh::~CameraMesh()
{ }


//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

void CameraMesh::Update()
{
	this->prCreateMesh();
}


//-----------------------------------------------------------------------------------
//	PRIVATE METHODS
//-----------------------------------------------------------------------------------

void CameraMesh::prCreateMesh()
{
	Mesh::Vertices	verts[9]{ };
	Mesh::Normals	norms[9]{ };
	Mesh::TexCoords texcoord[9]{ };
	Mesh::Indices	triList[8]{ };

	verts[0].x = -0.0f;
	verts[0].y = 0.0f;
	verts[0].z = 0.5f;
	norms[0].nx = 0.0f;
	norms[0].ny = 0.0f;
	norms[0].nz = 0.0f;
	texcoord[0].u = 0.0f;
	texcoord[0].v = 0.0f;

	triList[0].v0 = 0;
	triList[0].v1 = 1;
	triList[0].v2 = 2;

	triList[1].v0 = 0;
	triList[1].v1 = 2;
	triList[1].v2 = 3;

	triList[2].v0 = 0;
	triList[2].v1 = 3;
	triList[2].v2 = 4;

	triList[3].v0 = 0;
	triList[3].v1 = 4;
	triList[3].v2 = 1;

	// far
	triList[4].v0 = 1;
	triList[4].v1 = 2;
	triList[4].v2 = 3;

	// far
	triList[5].v0 = 3;
	triList[5].v1 = 4;
	triList[5].v2 = 1;

	// near
	triList[6].v0 = 5;
	triList[6].v1 = 6;
	triList[6].v2 = 7;

	// near
	triList[7].v0 = 7;
	triList[7].v1 = 8;
	triList[7].v2 = 5;


	Vec3 tmp;
	Camera3D* cam = Camera3DMan::Find(Camera::Name::FRUSTRUM);
	cam->UpdateCamera();

	cam->GetPos(tmp);
	verts[0].x = tmp[x];
	verts[0].y = tmp[y];
	verts[0].z = tmp[z];
	norms[0].nx = 0.0f;
	norms[0].ny = 0.0f;
	norms[0].nz = 0.0f;
	texcoord[0].u = 0.0f;
	texcoord[0].v = 0.0f;

	cam->GetFarTopRight(tmp);
	verts[1].x = tmp[x];
	verts[1].y = tmp[y];
	verts[1].z = tmp[z];
	norms[1].nx = 0.0f;
	norms[1].ny = 0.0f;
	norms[1].nz = 0.0f;
	texcoord[1].u = 0.0f;
	texcoord[1].v = 0.0f;

	cam->GetFarTopLeft(tmp);
	verts[2].x = tmp[x];
	verts[2].y = tmp[y];
	verts[2].z = tmp[z];
	norms[2].nx = 0.0f;
	norms[2].ny = 0.0f;
	norms[2].nz = 0.0f;
	texcoord[2].u = 0.0f;
	texcoord[2].v = 0.0f;

	cam->GetFarBottomLeft(tmp);
	verts[3].x = tmp[x];
	verts[3].y = tmp[y];
	verts[3].z = tmp[z];
	norms[3].nx = 0.0f;
	norms[3].ny = 0.0f;
	norms[3].nz = 0.0f;
	texcoord[3].u = 0.0f;
	texcoord[3].v = 0.0f;

	cam->GetFarBottomRight(tmp);
	verts[4].x = tmp[x];
	verts[4].y = tmp[y];
	verts[4].z = tmp[z];
	norms[4].nx = 0.0f;
	norms[4].ny = 0.0f;
	norms[4].nz = 0.0f;
	texcoord[4].u = 0.0f;
	texcoord[4].v = 0.0f;

	cam->GetNearTopRight(tmp);
	verts[5].x = tmp[x];
	verts[5].y = tmp[y];
	verts[5].z = tmp[z];
	norms[5].nx = 0.0f;
	norms[5].ny = 0.0f;
	norms[5].nz = 0.0f;
	texcoord[5].u = 0.0f;
	texcoord[5].v = 0.0f;

	cam->GetNearTopLeft(tmp);
	verts[6].x = tmp[x];
	verts[6].y = tmp[y];
	verts[6].z = tmp[z];
	norms[6].nx = 0.0f;
	norms[6].ny = 0.0f;
	norms[6].nz = 0.0f;
	texcoord[6].u = 0.0f;
	texcoord[6].v = 0.0f;

	cam->GetNearBottomLeft(tmp);
	verts[7].x = tmp[x];
	verts[7].y = tmp[y];
	verts[7].z = tmp[z];
	norms[7].nx = 0.0f;
	norms[7].ny = 0.0f;
	norms[7].nz = 0.0f;
	texcoord[7].u = 0.0f;
	texcoord[7].v = 0.0f;

	cam->GetNearBottomRight(tmp);
	verts[8].x = tmp[x];
	verts[8].y = tmp[y];
	verts[8].z = tmp[z];
	norms[8].nx = 0.0f;
	norms[8].ny = 0.0f;
	norms[8].nz = 0.0f;
	texcoord[8].u = 0.0f;
	texcoord[8].v = 0.0f;

	this->numVerts = sizeof(verts) / sizeof(Mesh::Vertices);
	this->numTris = sizeof(triList) / sizeof(Mesh::Indices);

	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo_verts);
	glGenBuffers(1, &this->vbo_norms);
	glGenBuffers(1, &this->vbo_texcoords);
	glGenBuffers(1, &this->vbo_index);

	assert(this->vbo_verts != 0);
	assert(this->vbo_norms != 0);
	assert(this->vbo_texcoords != 0);
	assert(this->vbo_index != 0);

	//Setup data and push to GPU
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Mesh::Vertices)* numVerts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIB_LOC_VERT, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertices), 0);
	glEnableVertexAttribArray(ATTRIB_LOC_VERT);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_norms);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Mesh::Normals)* this->numVerts), norms, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIB_LOC_NORMS, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Normals), 0);
	glEnableVertexAttribArray(ATTRIB_LOC_NORMS);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texcoords);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Mesh::TexCoords)* this->numVerts), texcoord, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIB_LOC_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::TexCoords), 0);
	glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORDS);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Mesh::Indices)* this->numTris), triList, GL_STATIC_DRAW);
}

