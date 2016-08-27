#include "crenderutils.h"
#include "window.h"
#include "Vertex.h"

//this is my branch
//there are many like it
//but this branch is my branch

//path for shaders
//		../res/shaders/simpleFrag
//		../res/shaders/simpleVert
void main()
{
	Window window;
	window.init();

	Vertex   vert[3] = { { 0,.5f,0,1, 1,0,0,1 },
						{.5f,-.5f,0,1, 0,1,0,1},
						{-.5f,-.5f,0,1, 0,1,1,1 }};

	unsigned tris[3] = { 0,1,2 };

	const char vsource[] =
		"#version 330\n"
		"layout(location = 0)in vec4 position;"
		"layout(location = 1)in vec4 color;"
		"out vec4 vColor;"
		"void main() {vColor = color; gl_Position = position;}";

	const char fsource[] =
		"#version 150\n"
		"in vec4 vColor;"
		"out vec4 outColor;"
		"void main() {outColor = vColor;}";

	Geometry geo = makeGeometry(vert , 3, tris, 3);
	Shader	 shade = makeShader(vsource, fsource);

	Shader shadow = loadShader("../res/shaders/simpleVert.txt","../res/shaders/simpleFrag.txt");


	Vertex n00b[3] = {  {0,.5f,0,1, 0,1,1,1,}, 
						{.5f,-.5f,0,1, 1,0,0,1}, 
						{.5,.5f,0,1, 1,1,0,1} };

	unsigned neeb[3] = {0,1,2};

	const char sourcev[] =
		"#version 330\n"
		"layout(location =0)in vec4 pos;"
		"layout(location =1)in vec4 col;"
		"out vec4 vCol;"
		"void main() {vCol = col; gl_Position = pos;}";

	const char sourcef[] =
		"#version 150\n"
		"in vec4 vCol;"
		"out vec4 outCol;"
		"void main() {outCol = vCol;}";

	Geometry joker = makeGeometry(n00b,3,neeb,3);
	Shader batman = makeShader(sourcev, sourcef);

	while (window.step())
	{
		draw(geo, shade);
		draw(joker, batman);
	}
	//first
	freeGeometry(geo);
	freeShader(shade);
	//second
	freeGeometry(joker);
	freeShader(batman);

	window.term();
	return;
}