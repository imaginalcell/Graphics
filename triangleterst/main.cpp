/*#include <iostream>

#include "Window.h"
#include "crenderutils.h"
#include "Gallery.h"

void main()
{
	Window window;
	Gallery gallery;

	window.Init(800, 600, "I got a potato");

	Vertex verts[] = { { 1,1,0,1 },{ 1,-1,0,1 },{ -1,-1,0,1 },{ -1,1,0,1 } };
	unsigned tris[] = { 0,1,2, 2,3,0 };

	gallery.MakeObject("quad", verts, 4, tris, 6);

	gallery.LoadObjectOBJ("Sphere", "../res/models/sphere.obj");
	gallery.LoadShader("Simple", "../res/shaders/SimpleVert.txt", "../res/shaders/SimpleFrag.txt");

	float time = 0;

	while (window.Step())
	{
		time += 0.0016667f;
		//Draw(gallery.GetShader("Simple"), gallery.GetObject("Sphere"), time);
		Draw(gallery.GetShader("Simple"), gallery.GetObject("quad"), time);
	}

	gallery.Term();
	window.Term();
}*/

#include "crenderutils.h"
#include "window.h"
#include "Input.h"
#include "Vertex.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

void main()
{
	Window context;
	context.Init(1280, 720);

	Framebuffer screen = { 0,1280,720 };

	Geometry quad = MakeGeometry(quad_verts, 4,
		quad_tris, 6);

	Shader simple = LoadShader("../res/shaders/simple.vert",
		"../res/shaders/simple.frag");

	while (context.Step())
	{
		tdraw(simple, quad, screen);
	}

	context.Term();
}