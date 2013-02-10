/*
 * decoderimage.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODERIMAGE_H
#define DECODERIMAGE_H

#include "resourcedecoder.h"

namespace base
{

class DecoderImage : public ResourceDecoder
{
public:
    DecoderImage() { }
    ~DecoderImage() { }

    sptr(Resource)  decode(const std::string &path);
    std::string     extension() const;
};

}

#endif // DECODERIMAGE_H
