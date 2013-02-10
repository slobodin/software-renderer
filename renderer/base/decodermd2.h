/*
 * decodermd2.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODERMD2_H
#define DECODERMD2_H

#include "resourcedecoder.h"

namespace base
{

class DecoderMD2 : public ResourceDecoder
{
public:
    DecoderMD2();
    ~DecoderMD2();

    sptr(Resource)  decode(const std::string &path);
    std::string     extension() const;
};

}

#endif // DECODERMD2_H
