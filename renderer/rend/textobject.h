/*
 * textobject.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "comm_pch.h"
#include "guiobject.h"

namespace rend
{

class TextObject : public GuiObject
{
    sptr(Texture) m_textPic;

    int m_cols, m_rows;
    int m_symbWidth, m_symbHeight;

public:
    TextObject(sptr(Texture) texturedFont, int cols, int rows);

    virtual const sptr(Texture) getTexture() const;

    void setText(const string &str);
    void setText(const char *str);
};

}

#endif // TEXTOBJECT_H
