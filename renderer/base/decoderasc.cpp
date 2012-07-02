/*
 * decoderasc.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "decoderasc.h"

#include "resource.h"

namespace base
{

DecoderASC::DecoderASC()
{
}

DecoderASC::~DecoderASC()
{
}

sptr(Resource) DecoderASC::decode(const string &path)
{
    syslog << "ASC files not supported yet" << logerr;
    return sptr(Resource)();
}

string DecoderASC::extension() const
{
    return "asc";
}

}
