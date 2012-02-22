#include "resourcemgr.h"
#include "ospath.h"
#include "decoderplg.h"

namespace base
{

ResourceMgr::ResourceMgr()
{
    SPTR(ResourceDecoder) plgDecoder(new DecoderPLG);
    // other decoders

    // add all
    m_decoders[plgDecoder->extention()] = plgDecoder;
}

ResourceMgr::~ResourceMgr()
{
}

SPTR(Resource) ResourceMgr::getResource(const string &pathString)
{
    // TODO: create full path
    OsPath path(pathString);

    return getResource(path);
}

SPTR(Resource) ResourceMgr::getResource(const OsPath &path)
{
    // ensure that we have decoder for this resource
    DecoderIterator dit = m_decoders.find(path.fileExtention());

    if (dit == m_decoders.end())
    {
        *syslog << "Unsupported file format. File:" << path.filePath() << logerr;
        // no such decoder
        // unsupported file format
        return SPTR(Resource)();
    }

    ResourceIterator rit = m_resources.find(path.filePath());

    // decode resource if need
    if (rit == m_resources.end())
    {
        SPTR(Resource) newResource = dit->second->decode(path);

        if (newResource.get())
            m_resources[path.filePath()] = newResource;
        else
        {
            *syslog << "Can't decode resource. File:" << path.filePath() << logerr;
            return SPTR(Resource)();
        }
    }

    return m_resources[path.filePath()];
}

}
