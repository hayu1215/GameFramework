#include"Window.h"

//�O���[�o���ϐ�
Window* g_pWindow = NULL;

//�֐��v���g�^�C�v�̐錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//OS���猩���E�B���h�E�v���V�[�W���[
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return g_pWindow->msgProc(hWnd, uMsg, wParam, lParam);
}

//�E�B���h�E�쐬
bool Window::initWindow(HINSTANCE hInstance,
                        INT iX, INT iY, INT iWidth, INT iHeight, LPCSTR WindowName) {
    g_pWindow = this;

    // �E�B���h�E�̐錾
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));

    //�E�B���h�E�̒�`
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.lpszClassName = WindowName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    //��`�����E�B���h�E�̓o�^
    RegisterClassEx(&wc);

    //�E�B���h�E�̍쐬
    m_hWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
                          0, 0, iWidth, iHeight, 0, 0, hInstance, 0);

    if (!m_hWnd) return false;

    //�E�C���h�E�̕\��
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return true;
}

//�E�B���h�E�v���V�[�W���[
LRESULT Window::msgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    //�A�v���P�[�V�����ɂƂ��ĕK�v�ȃ��b�Z�[�W�̏���
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
    //�A�v���P�[�V�����ɂƂ��ĕs�v�ȃ��b�Z�[�W�̏���
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}