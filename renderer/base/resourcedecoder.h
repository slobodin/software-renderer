/*
 * resourcedecoder.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RESOURCEDECODER_H
#define RESOURCEDECODER_H

#include "comm_pch.h"

#include "resource.h"
#include "ospath.h"

namespace base
{

class ResourceDecoder
{
public:
    ResourceDecoder() { }
    virtual ~ResourceDecoder() { }

    virtual sptr(Resource) decode(const OsPath &path) = 0;
    virtual string extention() const = 0;
};

}

#endif // RESOURCEDECODER_H
