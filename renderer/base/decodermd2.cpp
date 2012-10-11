/*
 * decodermd2.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "decodermd2.h"

namespace base
{

DecoderMD2::DecoderMD2()
{
}

DecoderMD2::~DecoderMD2()
{
}

sptr(Resource) DecoderMD2::decode(const string &/*path*/)
{
    syslog << "MD2 files not supported yet" << logerr;
    return sptr(Resource)();
}

string DecoderMD2::extension() const
{
    return "md2";
}

}
