/*
 * decoder3ds.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "decoder3ds.h"

namespace base
{

Decoder3DS::Decoder3DS()
{
}

Decoder3DS::~Decoder3DS()
{
}

sptr(Resource) Decoder3DS::decode(const string &/*path*/)
{
    syslog << "3DS files not supported yet" << logerr;
    return sptr(Resource)();
}

string Decoder3DS::extension() const
{
    return "3ds";
}

}
