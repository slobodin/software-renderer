/*
 * resourcemgr.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "resourcemgr.h"

#include "resource.h"
#include "resourcedecoder.h"
#include "osfile.h"
#include "decoderplg.h"
#include "decoderbspq3.h"

namespace base
{

bool ResourceMgr::checkFilePath(const string &path) const
{
}

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

sptr(Resource) ResourceMgr::getResource(const string &resourcepath)
{
    using namespace fs;

    path p(resourcepath);
    string fullpath = complete(p).string();

    auto rit = m_resources.find(fullpath);
    if (rit == m_resources.end())
    {
        // try to load

        // if unsuccessfull return NULL

        *syslog << "Getting null resource" << resourcepath << logwarn;
        return sptr(Resource)();
    }

    return m_resources[fullpath];
}

void ResourceMgr::loadResource(const string &resourcepath)
{
    using namespace fs;
    const char *error = "Loading resource:";

    path p(resourcepath);
    if (is_directory(p))
    {
        *syslog << error << resourcepath << "isn't a regular file" << logerr;
        return;
    }

    if (p.has_extension())
    {
        *syslog << error << resourcepath << "without extention" << logerr;
        return;
    }

    // ensure that we have decoder for this resource
    auto dit = m_decoders.find(p.extension().string());

    if (dit == m_decoders.end())
    {
        *syslog << error << resourcepath << "has unsupported file format." << logerr;
        return;
    }

    // if we already have the resource
    string fullpath = complete(p).string();

    auto rit = m_resources.find(fullpath);
    if (rit != m_resources.end())
    {
        *syslog << error << resourcepath << "already loaded." << logwarn;
        return;
    }

    sptr(Resource) newResource;
    try
    {
        newResource = dit->second->decode(fullpath);
    }
    catch(FileException)
    {
        return;
    }

    if (newResource)
        m_resources[fullpath] = newResource;
    else
    {
        *syslog << error << "Can't decode resource:" << resourcepath << logerr;
        return;
    }
}

void ResourceMgr::unloadResource(const string &resourcepath)
{
}

void ResourceMgr::addPath(const string &name)
{
    using namespace fs;

    path p(name);

    if (exists(p))
    {
        if (is_directory(p))
        {
            // if this path isn't in container
            m_loadablePaths.push_back(p);
        }
        else
        {
            *syslog << "Adding new path to resource manager:" << name << "isn't a directory" << logerr;
            return;
        }
    }
    else
        *syslog << "Adding new path to resource manager:" << name << "doesn't exist" <<logerr;
}

}
