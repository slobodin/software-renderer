/*
 * decoderimage.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "decoderimage.h"
#include "texture.h"

#include <easybmp/EasyBMP.h>

namespace base
{

sptr(Resource) DecoderImage::decode(const string &path)
{
    BMP image;
    if (!image.ReadFromFile(path.c_str()))
    {
        syslog << "Can't load image" << path << logwarn;
        return sptr(Resource)();
    }

    int bpp = image.TellBitDepth() / 8;
    int w = image.TellWidth();
    int h = image.TellHeight();

    vector<rend::Color3> pixels;
    pixels.reserve(w * h * bpp);

    for(int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            auto r = image.GetPixel(i, j).Red;
            auto g = image.GetPixel(i, j).Green;
            auto b = image.GetPixel(i, j).Blue;

            pixels.push_back(rend::Color3(r, g, b));
        }
    }

    auto texture = make_shared<rend::Texture>(pixels, w, h);

    boost::filesystem::path p(path);
    texture->setName(string("texture_") + boost::filesystem::basename(p));

    return texture;
}

string DecoderImage::extension() const
{
    return "bmp";       // ??
}

}
