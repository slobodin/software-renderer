/*
 * decoder3ds.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODER3DS_H
#define DECODER3DS_H

#include "comm_pch.h"

#include "resourcedecoder.h"

namespace base
{

class Decoder3DS : public ResourceDecoder
{
public:
    Decoder3DS();
    ~Decoder3DS();

    sptr(Resource)  decode(const string &path);
    string          extension() const;
};

}

#endif // DECODER3DS_H
