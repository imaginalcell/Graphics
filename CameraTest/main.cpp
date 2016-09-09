//#include <iostream>
//
//#include "Window.h"
//#include "crenderutils.h"
//#include "Gallery.h"
//#include "Timer.h"
//#include "Input.h"
//#include "Camera.h"
//
//#include "GLM\glm.hpp"
//#include "GLM\ext.hpp"
//
//void main()
//{
//	Window window;
//	Gallery gallery;
//	Time time;
//	Input input;
//
//	window.Init(1280, 720, "I got a potato");
//	gallery.Init();
//	input.Init(window);
//	time.Init();
//
//	gallery.LoadObjectOBJ("Sphere", "../res/models/sphere.obj");
//	gallery.LoadObjectOBJ("Cube", "../res/models/cube.obj");
//	//gallery.LoadShader("Simple", "../res/shaders/SimpleVert.txt", "../res/shaders/SimpleFrag.txt");
//	gallery.LoadShader("SimpleCamera", "../res/shaders/SimpleCameraVert.txt", "../res/shaders/SimpleCameraFrag.txt");
//
//	//unsigned char p[] = { 255, 255, 0 };
//
//	//Texture tex = makeTexture( 1, 1, 0x1907, p );
//
//	Texture tex = loadTexture("../res/textures/bigmisssteak.png");
//
//	glm::mat4 proj, view, model, model2, model3;
//	//proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
//	proj = glm::perspective(45.f, 1.f, 0.1f, 100.f);
//
//	view = glm::lookAt(glm::vec3(5.f, 5.f, 5.f),
//		glm::vec3(0.f, 0.f, 0.f),
//		glm::vec3(0.f, 1.f, 0.f));
//
//	//model = glm::scale(glm::vec3( .5f, .5f, .5f )) * glm::translate(glm::vec3(.1f, .1f, .1f));
//	model2 = glm::translate(glm::vec3(1, 0, 1));
//
//	float dt = 0;
//	float ct = 0;
//	float colorswitch = 0;
//
//	FlyCamera cam;
//	cam.JumpTo(glm::vec3(20, 0, 0));
//	cam.LookAt(glm::vec3(0, 0, 0));
//
//	while (window.Step())
//	{
//		time.Step();
//		input.Step();
//		dt = time.GetDeltaTime();
//
//		view = cam.GetView();
//		proj = cam.GetProjection();
//
//		cam.Update(input, time);
//
//		if (input.GetKeyState('D') == Input::DOWN) ct += time.GetDeltaTime();
//		if (input.GetKeyState('A') == Input::DOWN) ct -= time.GetDeltaTime();
//
//		if (input.GetKeyState('1') == Input::PRESS) colorswitch = 0;
//		if (input.GetKeyState('2') == Input::PRESS) colorswitch = 1;
//
//		model3 = glm::translate(glm::vec3(3, 0, 3)) * glm::rotate(ct, glm::vec3(0, 1, 0));
//
//		Draw(gallery.GetShader("SimpleCamera"), gallery.GetObject("Cube"), tex,
//			glm::value_ptr(model),
//			glm::value_ptr(view),
//			glm::value_ptr(proj));
//
//		/*Draw(gallery.GetShader("SimpleCamera"), gallery.GetObject("Sphere"),
//			glm::value_ptr(model2),
//			glm::value_ptr(view),
//			glm::value_ptr(proj), colorswitch);*/
//
//	
//
//	}
//
//	gallery.Term();
//	input.Term();
//	time.Term();
//	window.Term();
//}
#include "crenderutils.h"
#include "Window.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

void main()
{
	Window	window;
	window.Init(1280, 720);

	glm::mat4 view = glm::lookAt(glm::vec3(5.f, 5.f, 5.f),  // eye
								glm::vec3(0.f, 0.f, 0.f),  // center
								glm::vec3(0.f, 1.f, 0.f)); // up

	glm::mat4 proj = glm::perspective(45.f, 16 / 9.f, 1.f, 100.f);
	glm::mat4 modelC, modelS;

	Geometry soulspear = LoadObj("../res/models/soulspear.obj");
	Shader shader = LoadShader("../res/shaders/phongVert.txt",
		"../res/shaders/phongFrag.txt");

	Texture tarray[] = { loadTexture("..res/textures/soulspear_diffuse.tga"),
	loadTexture("../res/textures/soulspear_specular.tga"),
	loadTexture("../res/textures/soulspear_normal.tga")};

	float time = 0;
	while (window.Step())
	{
		time += 0.016f;
		modelC = glm::rotate(time, glm::normalize(glm::vec3(0, 1, 0)));
		modelS = glm::translate(glm::vec3(0, cos(time) * 6, 0));

		drawPhong(shader, soulspear, glm::value_ptr(modelC),
			glm::value_ptr(view),
			glm::value_ptr(proj),
			tarray, 3);
	}

	window.Term();
}