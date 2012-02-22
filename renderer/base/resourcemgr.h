#ifndef RESOURCEMGR_H
#define RESOURCEMGR_H

#include "comm_pch.h"

#include "resource.h"
#include "resourcedecoder.h"

namespace base
{

DECLARE_EXCEPTION(UnsupportedResource)

class ResourceMgr
{
    NONCOPYABLE(ResourceMgr)

    map<string, SPTR(Resource) > m_resources;
    map<string, SPTR(ResourceDecoder) > m_decoders;

public:
    ResourceMgr();
    ~ResourceMgr();
    
    SPTR(Resource) getResource(const string &pathString);
    SPTR(Resource) getResource(const OsPath &path);

private:
    typedef map<string, SPTR(ResourceDecoder) >::iterator DecoderIterator;
    typedef map<string, SPTR(ResourceDecoder) >::const_iterator ConstDecoderIterator;
    typedef map<string, SPTR(Resource) >::iterator ResourceIterator;
    typedef map<string, SPTR(Resource) >::const_iterator ConstResourceIterator;
};

}

#endif // RESOURCEMGR_H
