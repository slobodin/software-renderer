/*
 * resourcemgr.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RESOURCEMGR_H
#define RESOURCEMGR_H

#include "comm_pch.h"

#include "resource.h"
#include "resourcedecoder.h"

namespace base
{

DECLARE_EXCEPTION(UnsupportedResource)

class ResourceMgr : boost::noncopyable
{
    map<string, sptr(Resource) > m_resources;
    map<string, sptr(ResourceDecoder) > m_decoders;

public:
    ResourceMgr();
    ~ResourceMgr();
    
    sptr(Resource) getResource(const string &pathString);
    sptr(Resource) getResource(const OsPath &path);

private:
    typedef map<string, sptr(ResourceDecoder) >::iterator DecoderIterator;
    typedef map<string, sptr(ResourceDecoder) >::const_iterator ConstDecoderIterator;
    typedef map<string, sptr(Resource) >::iterator ResourceIterator;
    typedef map<string, sptr(Resource) >::const_iterator ConstResourceIterator;
};

}

#endif // RESOURCEMGR_H
