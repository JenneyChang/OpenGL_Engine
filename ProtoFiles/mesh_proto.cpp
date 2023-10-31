#include "mesh_proto.h"


//--------------------------------------------------------------------------------
//	CONSTRUCTION
//--------------------------------------------------------------------------------

mesh_proto::mesh_proto()
	: meshName{ 0 }, renderMode(RENDER_MODE::DEFAULT), hashid(0), numMeshes(0), triCount(0), vertCount(0),
	  vertices(), normals(), texCoords(), indicies(), weights(), joints(), invMats(), center(), radius(0.0f),
	  baseColor()
{ }

mesh_proto::~mesh_proto()
{ }

mesh_proto::mesh_proto(const mesh_proto& m)
	: meshName{ 0 }, renderMode(m.renderMode), hashid(m.hashid), triCount(m.triCount),
	  vertCount(m.vertCount), vertices(m.vertices), normals(m.normals),
	  texCoords(m.texCoords), indicies(m.indicies), weights(m.weights), joints(m.joints),
	  invMats(m.invMats), center(m.center), radius(m.radius), baseColor(m.baseColor)
{
	//file name
	memcpy_s(this->meshName, MESHNAME_SIZE, m.meshName, MESHNAME_SIZE);
}

mesh_proto& mesh_proto::operator=(const mesh_proto& m)
{
	if (this != &m)
	{
		//file name
		memset(this->meshName, 0, MESHNAME_SIZE);
		memcpy_s(this->meshName, MESHNAME_SIZE, m.meshName, MESHNAME_SIZE);

		this->renderMode = m.renderMode;
		this->hashid = m.hashid;
		this->triCount = m.triCount;
		this->vertCount = m.vertCount;
		this->vertices = m.vertices;
		this->normals = m.normals;
		this->texCoords = m.texCoords;
		this->indicies = m.indicies;
		this->weights = m.weights;
		this->joints = m.joints;
		this->invMats = m.invMats;
		this->center = m.center;
		this->radius = m.radius;
		this->baseColor = m.baseColor;
	}

	return *this;
}


//--------------------------------------------------------------------------------
//	SERIALIZATION
//--------------------------------------------------------------------------------

void mesh_proto::serialize(mesh_proto_mssg& out) const
{
	//mesh name
	std::string name((const char*)this->meshName, MESHNAME_SIZE);
	out.set_meshname(name);

	//mesh render data
	out.set_rendermode((mesh_proto_mssg_RENDER_MODE)this->renderMode);
	out.set_hashid(this->hashid);
	out.set_nummeshes(this->numMeshes);
	out.set_tricount(this->triCount);
	out.set_vertcount(this->vertCount);

	//vbos : vertices, normals, texture coordinates, colors, indices
	vbo_proto_mssg* vboMssg = new vbo_proto_mssg();
	this->vertices.serialize(*vboMssg);
	out.set_allocated_vertices(vboMssg);

	vboMssg = new vbo_proto_mssg();
	this->normals.serialize(*vboMssg);
	out.set_allocated_normals(vboMssg);

	vboMssg = new vbo_proto_mssg();
	this->texCoords.serialize(*vboMssg);
	out.set_allocated_texcoords(vboMssg);

	vboMssg = new vbo_proto_mssg();
	this->indicies.serialize(*vboMssg);
	out.set_allocated_indices(vboMssg);

	vboMssg = new vbo_proto_mssg();
	this->weights.serialize(*vboMssg);
	out.set_allocated_weights(vboMssg);

	vboMssg = new vbo_proto_mssg();
	this->joints.serialize(*vboMssg);
	out.set_allocated_joints(vboMssg);

	vboMssg = new vbo_proto_mssg();
	this->invMats.serialize(*vboMssg);
	out.set_allocated_invbind(vboMssg);

	//bounding sphere: center & radius
	vec3_proto_mssg* vecMssg = new vec3_proto_mssg();
	this->center.serialize(*vecMssg);
	out.set_allocated_bounding_sphere(vecMssg);

	out.set_radius(this->radius);

	// mesh base color
	vec4_proto_mssg* vec4Mssg = new vec4_proto_mssg();
	this->baseColor.serialize(*vec4Mssg);
	out.set_allocated_basecolor(vec4Mssg);

}

void mesh_proto::deserialize(const mesh_proto_mssg& in)
{
	//mesh name
	memcpy_s(this->meshName, MESHNAME_SIZE, in.meshname().data(), MESHNAME_SIZE);

	//mesh data
	this->renderMode = (RENDER_MODE)in.rendermode();
	this->hashid = in.hashid();
	this->numMeshes = in.nummeshes();
	this->triCount = in.tricount();
	this->vertCount = in.vertcount();

	//vbo data
	this->vertices.deserialize(in.vertices());
	this->normals.deserialize(in.normals());
	this->texCoords.deserialize(in.texcoords());
	this->indicies.deserialize(in.indices());

	this->weights.deserialize(in.weights());
	this->joints.deserialize(in.joints());
	this->invMats.deserialize(in.invbind());

	//bounding sphere
	this->center.deserialize(in.bounding_sphere());
	this->radius = in.radius();

	// base color
	this->baseColor.deserialize(in.basecolor());
}