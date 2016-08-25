#pragma once

struct  Geomentry
{
	//vertex buffer object: array of vertices
	//index buffer object : array of indeices (triangles)
	//vertex arrat object : groups the two with some formatting
	//size				  : number rof triangles

	unsigned vao, vbo, ibo, size;
};
Geomentry makeGeomentry(const struct Vertex *verts, size_t vsize,
						const unsigned int *tris, size_t tsize);

void freeGeomontry(Geomentry &);


struct Shader
{
	unsigned handle;
};
Shader makeShader(const char *vsource, const char *fsource);

void freeShader(Shader &);

void draw(const Geomentry &, const Shader &);