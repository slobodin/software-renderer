/*
 * decoderobj.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "decoderobj.h"

namespace base
{

DecoderOBJ::DecoderOBJ()
{
}

DecoderOBJ::~DecoderOBJ()
{
}

sptr(Resource) DecoderOBJ::decode(const string &path)
{
    syslog << "OBJ files not supported yet" << logerr;
    return sptr(Resource)();
}

string DecoderOBJ::extension() const
{
    return "obj";
}

}
