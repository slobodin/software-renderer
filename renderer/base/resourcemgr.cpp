/*
 * resourcemgr.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "resourcemgr.h"
#include "ospath.h"
#include "osfile.h"
#include "decoderplg.h"
#include "decoderbspq3.h"

namespace base
{

ResourceMgr::ResourceMgr()
{
    sptr(ResourceDecoder) plgDecoder(new DecoderPLG);
    sptr(ResourceDecoder) bspDecoder(new DecoderBSPQ3);
    // other decoders

    // add all
    m_decoders[plgDecoder->extention()] = plgDecoder;
    m_decoders[bspDecoder->extention()] = bspDecoder;
}

ResourceMgr::~ResourceMgr()
{
}

sptr(Resource) ResourceMgr::getResource(const string &pathString)
{
    // TODO: create full path
    OsPath path(pathString);

    return getResource(path);
}

sptr(Resource) ResourceMgr::getResource(const OsPath &path)
{
    // ensure that we have decoder for this resource
    DecoderIterator dit = m_decoders.find(path.fileExtention());

    if (dit == m_decoders.end())
    {
        *syslog << "Unsupported file format. File:" << path.filePath() << logerr;
        // no such decoder
        // unsupported file format
        return sptr(Resource)();
    }

    ResourceIterator rit = m_resources.find(path.filePath());

    // decode resource if need
    if (rit == m_resources.end())
    {
        sptr(Resource) newResource;
        try
        {
            newResource = dit->second->decode(path);
        }
        catch(FileException)
        {
            return sptr(Resource)();
        }

        if (newResource.get())
            m_resources[path.filePath()] = newResource;
        else
        {
            *syslog << "Can't decode resource. File:" << path.filePath() << logerr;
            return sptr(Resource)();
        }
    }

    return m_resources[path.filePath()];
}

}
