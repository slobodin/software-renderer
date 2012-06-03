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
}

string DecoderASC::extention() const
{
    return "asc";
}

}
