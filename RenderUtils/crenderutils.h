#pragma once

struct  Geometry
{
	//vertex buffer object: array of vertices
	//index buffer object : array of indeices (triangles)
	//vertex arrat object : groups the two with some formatting
	//size				  : number rof triangles

	unsigned vao, vbo, ibo, size;
};
Geometry makeGeometry(const struct Vertex *verts, size_t vsize,
						const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &);


struct Shader
{
	unsigned handle;
};
Shader makeShader(const char *vsource, const char *fsource);

void freeShader(Shader &);

void draw(const Geometry &, const Shader &);