/*
 * decoderimage.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODERIMAGE_H
#define DECODERIMAGE_H

#include "comm_pch.h"

#include "resourcedecoder.h"

namespace base
{

class DecoderImage : public ResourceDecoder
{
public:
    DecoderImage() { }
    ~DecoderImage() { }

    sptr(Resource)  decode(const string &path);
    string          extension() const;
};

}

#endif // DECODERIMAGE_H
