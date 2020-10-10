#pragma once

#include<dinput.h>

enum struct KeyCode : unsigned char {
    A = DIK_A,
    B = DIK_B,
    C = DIK_C,
    D = DIK_D,
    E = DIK_E,
    F = DIK_F,
    G = DIK_G,
    H = DIK_H,
    I = DIK_I,
    J = DIK_J,
    K = DIK_K,
    L = DIK_L,
    M = DIK_M,
    N = DIK_N,
    O = DIK_O,
    P = DIK_P,
    Q = DIK_Q,
    R = DIK_R,
    S = DIK_S,
    T = DIK_T,
    U = DIK_U,
    V = DIK_V,
    W = DIK_W,
    X = DIK_X,
    Y = DIK_Y,
    Z = DIK_Z,
    SPACE = DIK_SPACE,
    ESCAPE = DIK_ESCAPE,
    UP = DIK_UP,
    DOWN = DIK_DOWN,
    RIGHT = DIK_RIGHT,
    LEFT = DIK_LEFT,
    LSHIFT = DIK_LSHIFT,
    RSHIFT = DIK_RSHIFT,
    ENTER = DIK_RETURN,
    BACKSPACE = DIK_BACKSPACE,
};

class IKeyboard {
public:
    virtual ~IKeyboard() {};
    virtual void update() = 0;
    virtual bool getKey(KeyCode) = 0;
    virtual bool keyDown(KeyCode) = 0;
    virtual bool keyUp(KeyCode) = 0;
};