#pragma once
#include <string>
#include <map>
#include "crenderutils.h"
#include "globjects.h"
#include "Vertex.h"

//Render Object  : A thing that we render
//Shader Program : Pipline of shader scripts that divide and fill the screen

class Gallery
{
	std::map<std::string, Geometry> objects;
	std::map<std::string, Shader> shaders;

	//Shader makeShader(vsource,fsource)

	bool makeShader(const char* name, const char *vsource, const char *fsource);
	bool loadShader(const char* name, const char* vpath, const char *fpath);

	bool makeObjects(const char *name, const Vertex *verts, size_t vsize,
									const unsigned *tris, size_t tsize);

	bool loadObjectOBJ(const char *name, const char *path);

	const Geometry &getObject(const char *name);
	const Shader   &getShader(const char *name);

	bool init();
	bool term();
};