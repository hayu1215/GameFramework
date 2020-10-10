#pragma once

#include<Windows.h>

class Application {
public:
    Application();
    ~Application();

    void run(HINSTANCE hInstance);

private:
    bool init(HINSTANCE hInstance);
    void loop();
    void finalize();

    HWND m_hWnd;
};