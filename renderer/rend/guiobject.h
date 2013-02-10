/*
 * guiobject.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include "node.h"

namespace rend
{

class Texture;

//! Test class.
/**
  * For now it's just wrapper under texture. This object will render in 2d mode.
  */
class GuiObject : public Node
{
protected:
    sptr(Texture) m_texture;

public:
    GuiObject(sptr(Texture) texture);

    virtual const sptr(Texture) getTexture() const { return m_texture; }
};

}

#endif // GUIOBJECT_H
