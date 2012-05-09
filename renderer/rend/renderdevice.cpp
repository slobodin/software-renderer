/*
 * renderdevice.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "renderdevice.h"

#include <QImage>

#include <tcl8.5/tk.h>
#include <tcl8.5/tcl.h>
#include <third-party/cpptk-1.0.2/base/cpptkbase.h>

#include "framebuffer.h"

namespace rend
{

RenderDeviceQt::RenderDeviceQt(QImage *image)
    : m_image(image)
{
}

void RenderDeviceQt::flush(FrameBuffer &fb)
{
    if (!m_image)
        return;

    QRgb pixel;

    FrameBuffer::rgb *buf = fb.pixels();
    for (int x = 0; x < fb.width(); x++)
    {
        for (int y = 0; y < fb.height(); y++)
        {
            pixel = qRgb(buf->r, buf->g, buf->b);

            m_image->setPixel(x, y, pixel);

            buf++;

        }
    }
}

RenderDeviceTk::RenderDeviceTk(const string &widgetName)
    : m_widgetName(widgetName)
{
}

void RenderDeviceTk::flush(FrameBuffer &fb)
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

    block.pixelPtr = (unsigned char *)fb.pixels();
    block.width = fb.width();
    block.height = fb.height();
    block.pitch = 3 * fb.width();
    block.pixelSize = 3;
    block.offset[0] = 0;
    block.offset[1] = 1;
    block.offset[2] = 2;
    block.offset[3] = 0;

    Tk_PhotoPutBlock(fbinterp, fbphoto, &block, 0, 0, fb.width(), fb.height(), TK_PHOTO_COMPOSITE_SET);
}

}
