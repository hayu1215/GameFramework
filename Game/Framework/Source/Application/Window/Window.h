#pragma once

#include<Windows.h>

class Window
{
public:
	bool initWindow(HINSTANCE, INT, INT, INT, INT, LPCSTR);
	LRESULT msgProc(HWND, UINT, WPARAM, LPARAM);

public:
	HWND m_hWnd;
};