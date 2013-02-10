/*
 * decodermd2.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "decodermd2.h"

namespace base
{

DecoderMD2::DecoderMD2()
{
}

DecoderMD2::~DecoderMD2()
{
}

sptr(Resource) DecoderMD2::decode(const std::string &/*path*/)
{
    syslog << "MD2 files not supported yet" << logerr;
    return sptr(Resource)();
}

std::string DecoderMD2::extension() const
{
    return "md2";
}

}
