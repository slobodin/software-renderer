/*
 * decoderimage.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "decoderimage.h"
#include "texture.h"

#include <CImg.h>

namespace base
{

sptr(Resource) DecoderImage::decode(const string &path)
{
    cimg_library::CImg<unsigned char> image(path.c_str());
    if (image.depth() != 1 || image.spectrum() != 3)
    {
        syslog << "Invalid image" << path << logwarn;
        return sptr(Resource)();
    }

    auto texture = make_shared<rend::Texture>(image.data(), image.width(), image.height());

    boost::filesystem::path p(path);
    texture->setName(string("texture_") + boost::filesystem::basename(p));

    return texture;
}

string DecoderImage::extension() const
{
    return "bmp";       // ??
}

}
