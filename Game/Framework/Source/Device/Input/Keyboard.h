#pragma once

#include<dinput.h>
#include<wrl/client.h>
#include"IKeyboard.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

using Microsoft::WRL::ComPtr;

class Keyboard : public IKeyboard {
public:
    Keyboard();
    Keyboard(HWND, DWORD);
    ~Keyboard()override;

    //void setCooperativeLevel(HWND, DWORD);
    void update()override;
    bool getKey(KeyCode)override;
    bool keyDown(KeyCode)override;
    bool keyUp(KeyCode)override;

private:
    ComPtr<IDirectInput8A> m_dInput;
    ComPtr<IDirectInputDevice8A> m_keyDevice;

    BYTE m_keys[256];
    BYTE m_currentKeys[256];
};