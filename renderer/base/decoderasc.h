/*
 * decoderasc.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef DECODERASC_H
#define DECODERASC_H

#include "comm_pch.h"

#include "resourcedecoder.h"

namespace base
{

class DecoderASC : public ResourceDecoder
{
public:
    DecoderASC();
    ~DecoderASC();

    sptr(Resource)  decode(const string &path);
    string          extension() const;
};

}

#endif // DECODERASC_H
