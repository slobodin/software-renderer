/*
 * events.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "events.h"

namespace platform
{

KeyboardEvent::KeyboardEvent(unsigned long keycode)
{
    setKeyCode(keycode);
}

void KeyboardEvent::setKeyCode(unsigned long keycode)
{
    m_keycode = (KEY_CODE)keycode;  // windows keycode
}

KEY_CODE KeyboardEvent::keycode() const
{
    return m_keycode;
}

}
