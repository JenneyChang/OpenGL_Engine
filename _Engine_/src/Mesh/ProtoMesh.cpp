#include "ProtoMesh.h"
#include "MathEngine.h"
#include "File.h"
#include "ShaderLayout.h"

using namespace Azul;

//-----------------------------------------------------------------------------------
//	CONSTRUCTION
//-----------------------------------------------------------------------------------

ProtoMesh::ProtoMesh(const char* filename)
{
	assert(filename);

	//load proto mesh
	this->prUnpackProto(filename);
}

ProtoMesh::ProtoMesh(const char* filename, Texture* texture)
{
	assert(texture);
	assert(filename);

	//save ref to texture
	this->pTexture = texture;

	//load proto mesh
	this->prUnpackProto(filename);
}

ProtoMesh::~ProtoMesh()
{ }


//-----------------------------------------------------------------------------------
//	PUBLIC METHODS
//-----------------------------------------------------------------------------------

Texture* ProtoMesh::GetTexture()
{
	return this->pTexture;
}


//-----------------------------------------------------------------------------------
//	PRIVATE METHODS
//-----------------------------------------------------------------------------------

void ProtoMesh::prUnpackProto(const char* filename)
{
	//double check incoming
	assert(filename);

	//open and read proto.azul file
	File::Handle fh;
	File::Error status;

	status = File::Open(fh, filename, File::Mode::READ);
	assert(status == File::Error::SUCCESS);

	status = File::Seek(fh, File::Position::END, 0);
	assert(status == File::Error::SUCCESS);

	DWORD fileLength;
	status = File::Tell(fh, fileLength);
	assert(status == File::Error::SUCCESS);

	char* buffer = new char[fileLength]();
	assert(buffer);

	status = File::Seek(fh, File::Position::BEGIN, 0);
	assert(status == File::Error::SUCCESS);

	status = File::Read(fh, buffer, fileLength);
	assert(status == File::Error::SUCCESS);

	status = File::Close(fh);
	assert(status == File::Error::SUCCESS);


	//parse proto message
	mesh_proto_mssg mssg;
	mssg.ParseFromArray(buffer, fileLength);

	//deserialize it
	mesh_proto mproto;
	mproto.deserialize(mssg);

	//clean up
	delete[] buffer;

	//generate vao (and vbos)
	this->prCreateVAO(mproto);
}

void ProtoMesh::prCreateVAO(mesh_proto& mproto)
{
	//create & bind VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);

	//specs
	assert(mproto.renderMode == mesh_proto::RENDER_MODE::TRIANGLES);

	this->numTris = (int)mproto.triCount;
	assert(this->numTris > 0);

	this->numVerts = (int)mproto.vertCount;
	assert(this->numVerts > 0);

	//Load vertices data (location : 0)
	if (mproto.vertices.enabled)
	{
		//Create VBO: vertices (aka position)
		glGenBuffers(1, &this->vbo_verts);
		assert(this->vbo_verts != 0);

		//double check data
		assert(mproto.vertices.pData);
		assert(mproto.vertices.dataSize > 0);

		assert(mproto.vertices.attribIndex == ATTRIB_LOC_VERT);
		assert(mproto.vertices.type == vbo_proto::TYPE::VEC3);
		assert(mproto.vertices.component == vbo_proto::COMPONENT::FLOAT);

		//setup opengl vbo
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)mproto.vertices.dataSize, mproto.vertices.pData, GL_STATIC_DRAW);

		glVertexAttribPointer(mproto.vertices.attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(ProtoMesh::Vertices), 0);
		glEnableVertexAttribArray(mproto.vertices.attribIndex);
	}

	//Load normals data (location : 1)
	if (mproto.normals.enabled)
	{
		//Create VBO: normals
		glGenBuffers(1, &this->vbo_norms);
		assert(this->vbo_norms != 0);

		//double check data
		assert(mproto.normals.pData);
		assert(mproto.normals.dataSize > 0);

		assert(mproto.normals.attribIndex == ATTRIB_LOC_NORMS);
		assert(mproto.normals.type == vbo_proto::TYPE::VEC3);
		assert(mproto.normals.component == vbo_proto::COMPONENT::FLOAT);

		//setup opengl vbo
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_norms);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)mproto.normals.dataSize, mproto.normals.pData, GL_STATIC_DRAW);

		glVertexAttribPointer(mproto.normals.attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(ProtoMesh::Normals), 0);
		glEnableVertexAttribArray(mproto.normals.attribIndex);
	}

	//Load texture coordinates (location : 2)
	if (mproto.texCoords.enabled)
	{
		//Create VBO: texture coordinates
		glGenBuffers(1, &this->vbo_texcoords);
		assert(this->vbo_texcoords != 0);

		//double check data
		assert(mproto.texCoords.pData);
		assert(mproto.texCoords.dataSize > 0);

		assert(mproto.texCoords.attribIndex == ATTRIB_LOC_TEXCOORDS);
		assert(mproto.texCoords.type == vbo_proto::TYPE::VEC2);
		assert(mproto.texCoords.component == vbo_proto::COMPONENT::FLOAT);

		//setup opengl vbo
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texcoords);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)mproto.texCoords.dataSize, mproto.texCoords.pData, GL_STATIC_DRAW);

		glVertexAttribPointer(mproto.texCoords.attribIndex, 2, GL_FLOAT, GL_FALSE, sizeof(ProtoMesh::TexCoords), 0);
		glEnableVertexAttribArray(mproto.texCoords.attribIndex);
	}

	//Load indicies data
	if (mproto.indicies.enabled)
	{
		//Create VBO: indicies 
		glGenBuffers(1, &this->vbo_index);
		assert(this->vbo_index != 0);

		//double check data
		assert(mproto.indicies.type == vbo_proto::TYPE::SCALAR);
		assert(mproto.indicies.component == vbo_proto::COMPONENT::UNSIGNED_INT);
		assert(mproto.indicies.dataSize > 0);
		assert(mproto.indicies.pData);

		//setup opengl vbo
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)mproto.indicies.dataSize, mproto.indicies.pData, GL_STATIC_DRAW);
	}

	//Load weight data (location : 5)
	if (mproto.weights.enabled)
	{
		//Create VBO: weights
		glGenBuffers(1, &this->vbo_weights);
		assert(this->vbo_weights != 0);

		//double check data
		assert(mproto.weights.attribIndex == ATTRIB_LOC_WEIGHT);
		assert(mproto.weights.target == vbo_proto::TARGET::ARRAY_BUFFER);
		assert(mproto.weights.type == vbo_proto::TYPE::VEC4);
		assert(mproto.weights.component == vbo_proto::COMPONENT::FLOAT);
		assert(mproto.weights.dataSize > 0);
		assert(mproto.weights.pData);

		//setup opengl vbo
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_weights);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)mproto.weights.dataSize, mproto.weights.pData, GL_STATIC_DRAW);

		glVertexAttribPointer(mproto.weights.attribIndex, 4, GL_FLOAT, GL_FALSE, sizeof(ProtoMesh::Weights), 0);
		glEnableVertexAttribArray(mproto.weights.attribIndex);
	}

	//Load joint data (location : 6)
	if (mproto.joints.enabled)
	{
		//Create VBO: joints
		glGenBuffers(1, &this->vbo_joints);
		assert(this->vbo_joints != 0);

		//double check data
		assert(mproto.joints.attribIndex == ATTRIB_LOC_JOINT);
		assert(mproto.joints.target == vbo_proto::TARGET::ARRAY_BUFFER);
		assert(mproto.joints.type == vbo_proto::TYPE::VEC4);
		assert(mproto.joints.component == vbo_proto::COMPONENT::UNSIGNED_INT);
		assert(mproto.joints.dataSize > 0);
		assert(mproto.joints.pData);

		//setup opengl vbo
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_joints);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)mproto.joints.dataSize, mproto.joints.pData, GL_STATIC_DRAW);

		glVertexAttribIPointer(mproto.joints.attribIndex, 4, GL_UNSIGNED_INT, sizeof(ProtoMesh::Joints), 0);
		glEnableVertexAttribArray(mproto.joints.attribIndex);
	}

	//Load inverse bind matrices
	if (mproto.invMats.enabled)
	{
		assert(mproto.invMats.attribIndex == ATTRIB_LOC_INVBIND);
		assert(mproto.invMats.target == vbo_proto::TARGET::ARRAY_BUFFER);
		assert(mproto.invMats.type == vbo_proto::TYPE::MAT4);
		assert(mproto.invMats.component == vbo_proto::COMPONENT::FLOAT);
		assert(mproto.invMats.dataSize > 0);
		assert(mproto.invMats.pData);

		//Set SSBO
		this->poSSBO_InvBind->Set(mproto.invMats.count, sizeof(Mat4), mproto.invMats.pData);
	}

	if (mproto.radius > 0)
	{
		this->poSphere->radius = mproto.radius;
		this->poSphere->center.set(Vec3(mproto.center.x, mproto.center.y, mproto.center.z));
	}

	this->basecolor->set(mproto.baseColor.x, mproto.baseColor.y, mproto.baseColor.z, mproto.baseColor.w);

}