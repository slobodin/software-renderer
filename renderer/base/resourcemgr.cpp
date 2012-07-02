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

ResourceMgr::ResourceMgr()
{
    sptr(ResourceDecoder) plgDecoder(new DecoderPLG);
    sptr(ResourceDecoder) bspDecoder(new DecoderBSPQ3);
    // other decoders

    // add all
    m_decoders[plgDecoder->extension()] = plgDecoder;
    m_decoders[bspDecoder->extension()] = bspDecoder;

    // add path of the executable directory
//    m_loadablePaths.push_back(fs::current_path());
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

        syslog << "Getting null resource" << resourcepath << logwarn;
        return sptr(Resource)();
    }

    return m_resources[fullpath];
}

void ResourceMgr::loadResource(const string &resourcepath) try
{
    const char *error = "Loading resource:";

    fs::path p(resourcepath);
    if (is_directory(p))
    {
        syslog << error << resourcepath << "isn't a regular file" << logerr;
        return;
    }

    if (!p.has_extension())
    {
        syslog << error << resourcepath << "without extension" << logerr;
        return;
    }

    // ensure that we have decoder for this resource
    string extension = p.extension().string();
    if (extension.at(0) == '.')
    {
        extension.erase(extension.begin());
    }

    if (extension == "yaml")
        return;

    auto dit = m_decoders.find(extension);

    if (dit == m_decoders.end())
    {
        syslog << error << resourcepath << "has unsupported file format." << logerr;
        return;
    }

    // if we already have the resource
    string fullpath = fs::complete(p).string();

    auto rit = m_resources.find(fullpath);
    if (rit != m_resources.end())
    {
        syslog << error << resourcepath << "already loaded." << logwarn;
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
        syslog << error << "Can't decode resource:" << resourcepath << logerr;
        return;
    }
}
catch (fs::filesystem_error &e)
{
    syslog << "Boost filesystem exception occurred:" << e.what() << logerr;
}

void ResourceMgr::unloadResource(const string &resourcepath)
{
}

void ResourceMgr::loadResources() try
{
    for (auto loadablePath : m_loadablePaths)
    {
        vector<fs::path> dirEntries;

        if (fs::is_directory(loadablePath))
        {
            std::copy(fs::directory_iterator(loadablePath), fs::directory_iterator(),
                      std::back_inserter(dirEntries));

            for (auto p : dirEntries)
                loadResource(p.string());
        }
    }
}
catch (fs::filesystem_error &e)
{
    syslog << "Boost filesystem exception occurred:" << e.what() << logerr;
}

void ResourceMgr::addPath(const string &name) try
{
    using namespace fs;

    path p(name);

    if (exists(p))
    {
        if (is_directory(p))
        {
            // if this path isn't in container

            auto it = std::find_if(m_loadablePaths.begin(),
                                   m_loadablePaths.end(),
                                   [&](path &it){ return complete(p).string() == complete(it).string(); } );

            if (it == m_loadablePaths.end())
                m_loadablePaths.push_back(p);
            else
                syslog << "Path" << name << "already exists" << logwarn;
        }
        else
        {
            syslog << "Adding new path to resource manager:" << name << "isn't a directory" << logerr;
            return;
        }
    }
    else
        syslog << "Adding new path to resource manager:" << name << "doesn't exist" <<logerr;
}
catch (fs::filesystem_error &e)
{
    syslog << "Boost filesystem exception occurred:" << e.what() << logerr;
}

void ResourceMgr::listPath()
{
    syslog << "Path list:\n";
    for (auto p : m_loadablePaths)
        syslog << fs::complete(p).string() << "\n";

    syslog << logdebug;
}

}
