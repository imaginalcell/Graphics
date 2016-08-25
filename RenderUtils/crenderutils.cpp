#define GLEW_STATIC

#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include "Vertex.h"
#include "crenderutils.h"

Geomentry makeGeomentry(const Vertex * verts, size_t vsize, const unsigned int * tris, size_t tsize)
{
	Geomentry retval;
	retval.size = tsize;

	//define the var
	glCreateBuffers(1, &retval.vbo);
	glCreateBuffers(1, &retval.ibo);
	glCreateVertexArrays(1, &retval.vao);
	
	//scope the var
	glBindVertexArray(retval.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo); //scope our vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo);// scope triangles

	//init the var
		//new flaot [4]
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

	//attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)16);

	//unscope the var
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER ,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER ,0);
	
	return retval;
}

void freeGeomentry(Geomentry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);

	geo = { 0,0,0,0 };
}