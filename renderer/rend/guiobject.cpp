/*
 * guiobject.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "guiobject.h"

#include "texture.h"

namespace rend
{

GuiObject::GuiObject(sptr(Texture) texture)
    : m_texture(texture)
{
}

}
