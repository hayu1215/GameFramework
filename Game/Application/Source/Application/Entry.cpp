#include<Windows.h>
#include"Application.h"
#include<Framework/Source/Utility/Judge.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	Application app;
	app.run(hInstance);

	return 0;
}