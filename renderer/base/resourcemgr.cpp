/*
 * resourcemgr.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "resourcemgr.h"

#include "resource.h"
#include "resourcedecoder.h"
#include "osfile.h"
#include "decoderbspq3.h"
#include "decoderobj.h"
#include "decoderimage.h"
#include "mesh.h"
#include "sceneobject.h"

namespace base
{

ResourceMgr::ResourceMgr()
{
    sptr(ResourceDecoder) objDecoder(new DecoderOBJ);
    sptr(ResourceDecoder) imgDecoder(new DecoderImage);
    // other decoders

    // add all
    m_decoders[objDecoder->extension()] = objDecoder;
    m_decoders[imgDecoder->extension()] = imgDecoder;
}

ResourceMgr::~ResourceMgr()
{
}

sptr(Resource) ResourceMgr::getResource(const std::string &name)
{
    fs::path p(name);
    std::string fullpath;

    if (fs::is_directory(p))
        fullpath = fs::system_complete(p).string();
    else
        fullpath = name;

    // Find by full path.
    auto rit = m_resources.find(fullpath);
    // if can't find -> load resource
    if (rit == m_resources.end())
    {
        loadResource(fullpath);

        // find again
        rit = m_resources.find(fullpath);

        // if can't find again -> search in all directories
        if (rit == m_resources.end())
        {
            for (auto dir : m_loadablePaths)
            {
                fs::path p(dir);
                p /= name;

                try {
                    rit = m_resources.find(fs::system_complete(p).string());
                    if (rit != m_resources.end())
                    {
                        return rit->second;
                    }
                }
                catch (...) { }
            }

            // else -> find by name
            rit = std::find_if(m_resources.begin(), m_resources.end(),
                               [&](std::map<std::string, sptr(Resource) >::value_type &val)
                               { return val.second->getName() == name; } );     // do you like C++ too??

            // no such resource
            if (rit == m_resources.end())
            {
                syslog << "No such resource" << name << logwarn;
                return sptr(Resource)();
            }
            else
            {
                return rit->second;
            }
        }
        else
            return m_resources[fullpath];
    }
    else
        return m_resources[fullpath];
}

void ResourceMgr::loadResource(const std::string &resourcepath) try
{
    const char *error = "Loading resource:";

    fs::path p(resourcepath);
    if (fs::is_directory(p))
    {
        syslog << error << resourcepath << "isn't a regular file" << logerr;
        return;
    }
    
    if (p.extension() == std::string())
        return;

    // ensure that we have decoder for this resource
    std::string extension = p.extension();
    if (extension.at(0) == '.')
        extension.erase(extension.begin());

    auto dit = m_decoders.find(extension);
    // unsupported
    if (dit == m_decoders.end())
        return;

    // if we already have the resource
    std::string fullpath = fs::system_complete(p);

    auto rit = m_resources.find(fullpath);
    if (rit != m_resources.end())
    {
        syslog << error << resourcepath << "already loaded." << logwarn;
        return;
    }

    if (!fs::exists(fs::system_complete(p)))
        return;

    sptr(Resource) newResource;

    newResource = dit->second->decode(fullpath);

    if (newResource)
    {
        newResource->additionalLoading(this);       // if we have textures, need to load them too. Bad design, actually...
        m_resources[fullpath] = newResource;
    }
    else
    {
        syslog << error << "Can't decode resource:" << resourcepath << logerr;
        return;
    }
}
catch (std::tr2::sys::filesystem_error &e)
{
    syslog << "Boost filesystem exception occurred:" << e.what() << logerr;
}

void ResourceMgr::unloadResource(const std::string &/*resourcepath*/)
{
    // TODO:
}

void ResourceMgr::loadAllResources() try
{
    for (auto loadablePath : m_loadablePaths)
    {
        std::vector<fs::path> dirEntries;

        if (fs::is_directory(loadablePath))
        {
            std::copy(fs::directory_iterator(loadablePath), fs::directory_iterator(),
                      std::back_inserter(dirEntries));

            for (auto p : dirEntries)
                loadResource(loadablePath / p);
        }
    }

    syslog << "Loaded resources:\n";
    for (auto resource : m_resources)
    {
        syslog << resource.first << "with name" << resource.second->getName() << "\n";
    }
    syslog << logmess;
}
catch (std::tr2::sys::filesystem_error &e)
{
    syslog << "Boost filesystem exception occurred:" << e.what() << logerr;
}

void ResourceMgr::addPath(const std::string &name) try
{
    if (name.empty())
    {
        syslog << "Trying to add empty resources path" << logwarn;
        return;
    }

    fs::path p(name);

    if (exists(p))
    {
        if (is_directory(p))
        {
            // if this path isn't in container

            auto it = std::find_if(m_loadablePaths.begin(),
                                   m_loadablePaths.end(),
                                   [&](fs::path &it){ return fs::system_complete(p).string() == fs::system_complete(it).string(); } );

            if (it == m_loadablePaths.end())
                m_loadablePaths.push_back(p);
            else
                syslog << "Path" << name << "already exists" << logwarn;
        }
        else
        {
            syslog << "Adding new path to resource manager:" << name << "isn't a directory" << logwarn;
            return;
        }
    }
    else
        syslog << "Adding new path to resource manager:" << name << "doesn't exist" <<logwarn;
}
catch (std::tr2::sys::filesystem_error &e)
{
    syslog << "Boost filesystem exception occurred:" << e.what() << logerr;
}

void ResourceMgr::listPath()
{
    syslog << "Path list:\n";
    for (auto p : m_loadablePaths)
        syslog << fs::system_complete(p).string() << "\n";

    syslog << logdebug;
}

}
