/*
 * xviewport.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef XVIEWPORT_H
#define XVIEWPORT_H

#include "renderer.h"

class XViewport : public rend::Viewport
{
public:
    XViewport(int width, int height, boost::shared_ptr<rend::Camera> camera);

    void flush(unsigned char *pixels);
};

#endif // XVIEWPORT_H
