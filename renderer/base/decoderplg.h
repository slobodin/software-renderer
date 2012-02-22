#ifndef DECODERPLG_H
#define DECODERPLG_H

#include "comm_pch.h"

#include "resourcedecoder.h"

namespace base
{

class DecoderPLG : public ResourceDecoder
{
public:
    DecoderPLG();
    ~DecoderPLG();

    SPTR(Resource) decode(const OsPath &path);
    string extention() const;
};

}

#endif // DECODERPLG_H
