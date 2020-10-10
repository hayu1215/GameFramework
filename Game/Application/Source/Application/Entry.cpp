#include<Windows.h>
#include"Application.h"
#include<Framework/Source/Utility/Judge.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT) {
    Application app;
    app.run(hInstance);
    //Application* app = new Application;
    //app->run(hInstance);
    //delete app;
    return 0;
}