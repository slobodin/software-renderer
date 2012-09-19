/*
 * events.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "events.h"

namespace platform
{

#if defined(LINUX_VERSION)

#include <X11/Xlib.h>
#include <X11/keysym.h>

struct LinuxKeymap : boost::noncopyable
{
    static LinuxKeymap &get()
    {
        static LinuxKeymap keymapLinux;
        return keymapLinux;
    }

    KEY_CODE getKeyCode(KeySym linuxKey)
    {
        auto it = keymap.find(linuxKey);
        if (it == keymap.end())
            return KEY_NONE;
        else
            return it->second;
    }

private:
    LinuxKeymap();

    std::map<KeySym, KEY_CODE> keymap;
};

LinuxKeymap::LinuxKeymap()
{
    keymap[XK_BackSpace] = KEY_BACK;

    keymap[XK_Tab] = KEY_TAB;
    keymap[XK_Return] = KEY_RETURN;
    keymap[XK_Escape] = KEY_ESCAPE;
    keymap[XK_KP_Space] = KEY_SPACE;
    keymap[XK_space] = KEY_SPACE;
    keymap[XK_KP_Left] = KEY_LEFT;
    keymap[XK_Left] = KEY_LEFT;
    keymap[XK_KP_Up] = KEY_UP;
    keymap[XK_Up] = KEY_UP;
    keymap[XK_KP_Right] = KEY_RIGHT;
    keymap[XK_Right] = KEY_RIGHT;
    keymap[XK_KP_Down] = KEY_DOWN;
    keymap[XK_Down] = KEY_DOWN;
    keymap[XK_KP_0] = KEY_KEY_0;
    keymap[XK_KP_1] = KEY_KEY_1;
    keymap[XK_KP_2] = KEY_KEY_2;
    keymap[XK_KP_3] = KEY_KEY_3;
    keymap[XK_KP_4] = KEY_KEY_4;
    keymap[XK_KP_5] = KEY_KEY_5;
    keymap[XK_KP_6] = KEY_KEY_6;
    keymap[XK_KP_7] = KEY_KEY_7;
    keymap[XK_KP_8] = KEY_KEY_8;
    keymap[XK_KP_9] = KEY_KEY_9;
    keymap[XK_0] = KEY_KEY_0;
    keymap[XK_1] = KEY_KEY_1;
    keymap[XK_2] = KEY_KEY_2;
    keymap[XK_3] = KEY_KEY_3;
    keymap[XK_4] = KEY_KEY_4;
    keymap[XK_5] = KEY_KEY_5;
    keymap[XK_6] = KEY_KEY_6;
    keymap[XK_7] = KEY_KEY_7;
    keymap[XK_8] = KEY_KEY_8;
    keymap[XK_9] = KEY_KEY_9;
    keymap[XK_A] = KEY_KEY_A;
    keymap[XK_B] = KEY_KEY_B;
    keymap[XK_C] = KEY_KEY_C;
    keymap[XK_D] = KEY_KEY_D;
    keymap[XK_E] = KEY_KEY_E;
    keymap[XK_F] = KEY_KEY_F;
    keymap[XK_G] = KEY_KEY_G;
    keymap[XK_H] = KEY_KEY_H;
    keymap[XK_I] = KEY_KEY_I;
    keymap[XK_J] = KEY_KEY_J;
    keymap[XK_K] = KEY_KEY_K;
    keymap[XK_L] = KEY_KEY_L;
    keymap[XK_M] = KEY_KEY_M;
    keymap[XK_N] = KEY_KEY_N;
    keymap[XK_O] = KEY_KEY_O;
    keymap[XK_P] = KEY_KEY_P;
    keymap[XK_Q] = KEY_KEY_Q;
    keymap[XK_R] = KEY_KEY_R;
    keymap[XK_S] = KEY_KEY_S;
    keymap[XK_T] = KEY_KEY_T;
    keymap[XK_U] = KEY_KEY_U;
    keymap[XK_V] = KEY_KEY_V;
    keymap[XK_W] = KEY_KEY_W;
    keymap[XK_X] = KEY_KEY_X;
    keymap[XK_Y] = KEY_KEY_Y;
    keymap[XK_Z] = KEY_KEY_Z;
    keymap[XK_a] = KEY_KEY_A;
    keymap[XK_b] = KEY_KEY_B;
    keymap[XK_c] = KEY_KEY_C;
    keymap[XK_d] = KEY_KEY_D;
    keymap[XK_e] = KEY_KEY_E;
    keymap[XK_f] = KEY_KEY_F;
    keymap[XK_g] = KEY_KEY_G;
    keymap[XK_h] = KEY_KEY_H;
    keymap[XK_i] = KEY_KEY_I;
    keymap[XK_j] = KEY_KEY_J;
    keymap[XK_k] = KEY_KEY_K;
    keymap[XK_l] = KEY_KEY_L;
    keymap[XK_m] = KEY_KEY_M;
    keymap[XK_n] = KEY_KEY_N;
    keymap[XK_o] = KEY_KEY_O;
    keymap[XK_p] = KEY_KEY_P;
    keymap[XK_q] = KEY_KEY_Q;
    keymap[XK_r] = KEY_KEY_R;
    keymap[XK_s] = KEY_KEY_S;
    keymap[XK_t] = KEY_KEY_T;
    keymap[XK_u] = KEY_KEY_U;
    keymap[XK_v] = KEY_KEY_V;
    keymap[XK_w] = KEY_KEY_W;
    keymap[XK_x] = KEY_KEY_X;
    keymap[XK_y] = KEY_KEY_Y;
    keymap[XK_z] = KEY_KEY_Z;
    keymap[XK_F1] = KEY_F1;
    keymap[XK_F2] = KEY_F2;
    keymap[XK_F3] = KEY_F3;
    keymap[XK_F4] = KEY_F4;
    keymap[XK_F5] = KEY_F5;
    keymap[XK_F6] = KEY_F6;
    keymap[XK_F7] = KEY_F7;
    keymap[XK_F8] = KEY_F8;
    keymap[XK_F9] = KEY_F9;
    keymap[XK_F10] = KEY_F10;
    keymap[XK_F11] = KEY_F11;
    keymap[XK_F12] = KEY_F12;
}

#endif

KeyboardEvent::KeyboardEvent(unsigned long keycode)
{
    setKeyCode(keycode);
}

void KeyboardEvent::setKeyCode(unsigned long keycode)
{
#if defined(LINUX_VERSION)
    m_keycode = LinuxKeymap::get().getKeyCode(keycode);
#elif defined(WINDOWS_VERSION)
    m_keycode = (KEY_CODE)keycode;
#elif defined(TK_VERSION)
    m_keycode = (KEY_CODE)keycode;  // windows keycode
#else
#error Unsupported OS
#endif
}

KEY_CODE KeyboardEvent::keycode() const
{
    return m_keycode;
}

}
