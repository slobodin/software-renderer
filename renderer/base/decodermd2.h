/*
 * decodermd2.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODERMD2_H
#define DECODERMD2_H

#include "comm_pch.h"

#include "resourcedecoder.h"

namespace base
{

class DecoderMD2 : public ResourceDecoder
{
public:
    DecoderMD2();
    ~DecoderMD2();

    sptr(Resource)  decode(const string &path);
    string          extention() const;
};

}

#endif // DECODERMD2_H
