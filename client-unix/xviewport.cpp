/*
 * xviewport.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "xviewport.h"

XViewport::XViewport(int width, int height, boost::shared_ptr<rend::Camera> camera)
    : Viewport(width, height, camera)
{
}

void XViewport::flush(unsigned char *pixels)
{
}
