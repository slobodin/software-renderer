/*
 * textobject.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "textobject.h"

#include "texture.h"

namespace rend
{

TextObject::TextObject(sptr(Texture) texturedFont, int cols, int rows)
    : GuiObject(texturedFont),
      m_cols(cols),
      m_rows(rows)
{
    m_textPic = make_shared<Texture>(vector<Color4>(), 0, 0);
    if (m_texture)
    {
        m_symbWidth = m_texture->width() / cols;
        m_symbHeight = m_texture->height() / rows;
    }
    else
    {
        m_symbWidth = 0;
        m_symbHeight = 0;
    }
}

const sptr(Texture) TextObject::getTexture() const
{
    return m_textPic;
}

void TextObject::setText(const string &str)
{
    if (str.empty())
        return;

    if (!m_texture)
        return;

    vector<Color4> resultPixmap;
    // scanlining
    for (int ln = 0; ln < m_symbHeight; ln++)
    {
        for (char c : str)
        {
            int symbX = (c % m_cols) * m_symbWidth;
            int symbY = (c / m_cols) * m_symbHeight;

            auto pixels = m_texture->getLine(symbY + ln, symbX, symbX + m_symbWidth);
            resultPixmap.insert(resultPixmap.end(), pixels.begin(), pixels.end());
        }
    }

    m_textPic = make_shared<Texture>(resultPixmap, m_symbWidth * str.size(), m_symbHeight);
}

void TextObject::setText(const char *str)
{
    setText(string(str));
}

}
