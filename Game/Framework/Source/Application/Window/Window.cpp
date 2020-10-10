#include"Window.h"

//グローバル変数
Window* g_pWindow = NULL;

//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//OSから見たウィンドウプロシージャー
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return g_pWindow->msgProc(hWnd, uMsg, wParam, lParam);
}

//ウィンドウ作成
bool Window::initWindow(HINSTANCE hInstance,
                        INT iX, INT iY, INT iWidth, INT iHeight, LPCSTR WindowName) {
    g_pWindow = this;

    // ウィンドウの宣言
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));

    //ウィンドウの定義
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.lpszClassName = WindowName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    //定義したウィンドウの登録
    RegisterClassEx(&wc);

    //ウィンドウの作成
    m_hWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
                          0, 0, iWidth, iHeight, 0, 0, hInstance, 0);

    if (!m_hWnd) return false;

    //ウインドウの表示
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return true;
}

//ウィンドウプロシージャー
LRESULT Window::msgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    //アプリケーションにとって必要なメッセージの処理
    switch (iMsg) {
    case WM_KEYDOWN:
        switch ((char)wParam) {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    //アプリケーションにとって不要なメッセージの処理
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}