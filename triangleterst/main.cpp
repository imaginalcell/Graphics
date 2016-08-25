#include "crenderutils.h"
#include "window.h"
#include "Vertex.h"

//this is my branch
//there are many like it
//but this branch is my branch

void main()
{
	Window window;
	window.init();

	Vertex   vert[3] = { { 0,.5f,0,1 },
						{.5f,-.5f,0,1},
						{-.5f,-.5f,0,1} };

	unsigned tris[3] = { 0,1,2 };

	const char vsource[] =
		"#version 150\n"
		"in vec4 position;"
		"void main() {gl_Position = position;}";
	const char fsource[] =
		"#version 150\n"
		"out vec4 outColor;"
		"void main () {outColor = vec4(0.0, 1.0,0.0,1.0); }";

	Geometry geoff = makeGeometry(vert , 3, tris, 3);
	Shader	  shade = makeShader(vsource, fsource);

	while (window.step())
	{
		draw(geoff, shade);
	}
	
	freeGeometry(geoff);
	freeShader(shade);
	window.term();
	return;
}