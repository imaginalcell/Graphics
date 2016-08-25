#include "crenderutils.h"
#include "window.h"

//this is my branch
//there are many like it
//but this branch is my branch

void main()
{
	Window window;
	window.init();

	while (window.step());
	
	window.term();
	return;
}