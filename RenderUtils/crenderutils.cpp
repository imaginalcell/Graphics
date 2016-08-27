#define GLEW_STATIC

#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include "Vertex.h"
#include "crenderutils.h"
#include <cstdio>

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

long copyFileToArray(char *dest, size_t dlen, const char *path)
{
	FILE *fp;
	fopen_s(&fp, path, "r");	// open file	
	if (!fp) return 0;

	fseek(fp, 0L, SEEK_END);		// jump to end of file
	long size = ftell(fp);			// determine how many chars we passed
	rewind(fp);						// go back to beginning

	long lastIndex = fread_s(dest, dlen, 1, size, fp);

	dest[lastIndex] = 0;

	fclose(fp);
	return size;
}

#include <fstream>
#include <istream>
#include <string>

std::string cppStyleFileToString(const char *path)
{
	std::ifstream infile{ path };
	std::string file_contents{ std::istreambuf_iterator<char>(infile),
		std::istreambuf_iterator<char>() };
	return file_contents;
}

Shader loadShader(const char * vpath, const char * fpath)
{
	char vsource[5012]; //max of 5012 characters in source
	char fsource[5012];	//will probably change that later

	copyFileToArray(vsource, 5012, vpath);
	copyFileToArray(fsource, 5012, fpath);

	std::string vs = cppStyleFileToString(vpath);
	std::string fs = cppStyleFileToString(fpath);

	const char *vCode = vs.c_str(), *fCode = fs.c_str();

	return makeShader(vCode,fCode);
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

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "OBJ\tiny_obj_loader.h"
#include <random>

Geometry loadOBJ(const char *path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	Vertex   *verts = new Vertex[attrib.vertices.size() / 3];
	unsigned * tris = new unsigned[shapes[0].mesh.indices.size()];

	for (int i = 0; i < attrib.vertices.size() / 3; ++i)
	{
		verts[i] = { attrib.vertices[i * 3],
			attrib.vertices[i * 3 + 1],
			attrib.vertices[i * 3 + 2], 1 };

		verts[i].color[0] = rand() * 1.0f / RAND_MAX;
		verts[i].color[1] = rand() * 1.0f / RAND_MAX;
		verts[i].color[2] = rand() * 1.0f / RAND_MAX;
		verts[i].color[3] = 1;
	}

	for (int i = 0; i < shapes[0].mesh.indices.size(); ++i)
		tris[i] = shapes[0].mesh.indices[i].vertex_index;

	Geometry retval = makeGeometry(verts, attrib.vertices.size() / 3,
		tris, shapes[0].mesh.indices.size());

	delete[] verts;
	delete[] tris;
	// then we can call makeGeometry as per normal.
	return retval;
}