/*
 * decoderobj.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODEROBJ_H
#define DECODEROBJ_H

#include "comm_pch.h"

#include "resourcedecoder.h"

namespace base
{

class DecoderOBJ : public ResourceDecoder
{
public:
    DecoderOBJ();
    ~DecoderOBJ();

    sptr(Resource)  decode(const string &path);
    string          extension() const;
};

}

#endif // DECODEROBJ_H
