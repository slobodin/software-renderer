/*
 * renderdevice.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef RENDERDEVICE_H
#define RENDERDEVICE_H

#include "comm_pch.h"

class QImage;

namespace rend
{

class FrameBuffer;

class RenderDevice
{
public:
    RenderDevice() { }
    virtual ~RenderDevice() { }

    virtual void flush(FrameBuffer &fb) = 0;
};

class RenderDeviceQt : public RenderDevice
{
    QImage *m_image;
public:
    RenderDeviceQt(QImage *image);

    void flush(FrameBuffer &fb);
};

class RenderDeviceTk : public RenderDevice
{
    string m_widgetName;
public:
    RenderDeviceTk(const string &widgetName);

    void flush(FrameBuffer &fb);
};

}

#endif // RENDERDEVICE_H
