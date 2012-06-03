/*
 * baseapptk.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "baseapptk.h"

#include <third-party/cpptk-1.0.2/cpptk.h>

using namespace Tk;

BaseAppTk::BaseAppTk(char *argv[])
{
    Tk::init(argv[0]);
}

BaseAppTk::~BaseAppTk()
{
}

void BaseAppTk::run()
{
}

void ViewportTkImage::flush(unsigned char *pixels)
{
    if (m_widgetName.empty())
        return;

    Tk_PhotoHandle fbphoto;
    Tk_PhotoImageBlock block;
    Tcl_Interp *fbinterp = Tk::globalTclInterpret;

    if ((fbphoto = Tk_FindPhoto(fbinterp, m_widgetName.c_str())) == NULL)
    {
        *syslog << "Image creation unsuccessful. Can't find" << m_widgetName.c_str() << logerr;
        return;
    }

    block.pixelPtr = pixels;
    block.width = m_width;
    block.height = m_height;
    block.pitch = 3 * m_width;
    block.pixelSize = 3;
    block.offset[0] = 0;
    block.offset[1] = 1;
    block.offset[2] = 2;
    block.offset[3] = 0;

    Tk_PhotoPutBlock(fbinterp, fbphoto, &block, 0, 0, m_width, m_width, TK_PHOTO_COMPOSITE_SET);
}
