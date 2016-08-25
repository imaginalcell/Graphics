#define GLEW_STATIC

#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include "Vertex.h"
#include "crenderutils.h"

Geometry makeGeometry(const Vertex * verts, size_t vsize, const unsigned int * tris, size_t tsize)
{
	Geometry retval;
	
	//define the var
	glGenBuffers(1, &retval.vbo);
	glGenBuffers(1, &retval.ibo);
	glGenVertexArrays(1, &retval.vao);
	
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
	retval.size = tsize;
	return retval;
}

void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);

	geo = { 0,0,0,0 };
}

Shader makeShader(const char * vsource, const char * fsource)
{
	Shader retval;

	retval.handle = glCreateProgram();
	//create our var
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	//init our var
	glShaderSource(vs, 1, &vsource, 0);
	glShaderSource(fs, 1, &fsource, 0);
	//compile shader
	glCompileShader(vs);
	glCompileShader(fs);
	//link the shaders into a single program
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glLinkProgram(retval.handle);
	//no longer need em
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

void freeShader(Shader &slade)
{
	glDeleteProgram(slade.handle);
	slade.handle = 0;
}

void draw(const Geometry &geo, const Shader &sad)
{
	glUseProgram(sad.handle);
	glBindVertexArray(geo.vao);

	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);

}