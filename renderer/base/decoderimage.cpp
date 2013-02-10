/*
 * decoderimage.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "decoderimage.h"

#include "texture.h"
#include <CImg/CImg.h>

namespace base
{

sptr(Resource) DecoderImage::decode(const std::string &path)
{
    cimg_library::CImg<uint32_t> image;
    image.load(path.c_str());
    
    int bpp = image.spectrum();
    int w = image.width();
    int h = image.height();

    std::vector<rend::Color3> pixels;
    pixels.reserve(image.size());

    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
#ifdef _WIN32
            // swap r and b
            // something wrong with SetDIBitsToDevice
            uint32_t r = image(i, j, 0, 2);
            uint32_t g = image(i, j, 0, 1);
            uint32_t b = image(i, j, 0, 0);
#else
#error "Unsupported OS."
#endif
            pixels.push_back(rend::Color3(r, g, b));
        }
    }

    auto texture = std::make_shared<rend::Texture>(pixels, w, h);

    std::tr2::sys::path p(path);
    texture->setName(std::string("texture_") + std::tr2::sys::basename(p));

    return texture;
}

std::string DecoderImage::extension() const
{
    return "bmp";
}

}
