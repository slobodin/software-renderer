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
#include "decoderasc.h"
#include "decodercob.h"
#include "decoderobj.h"
#include "decoderimage.h"
#include "mesh.h"
#include "sceneobject.h"

namespace base
{

ResourceMgr::ResourceMgr()
{
    sptr(ResourceDecoder) plgDecoder(new DecoderPLG);
    sptr(ResourceDecoder) ascDecoder(new DecoderASC);
    sptr(ResourceDecoder) cobDecoder(new DecoderCOB);
    sptr(ResourceDecoder) objDecoder(new DecoderOBJ);
    sptr(ResourceDecoder) imgDecoder(new DecoderImage);
    sptr(ResourceDecoder) bspDecoder(new DecoderBSPQ3);
    // other decoders

    // add all
    m_decoders[plgDecoder->extension()] = plgDecoder;
    m_decoders[ascDecoder->extension()] = ascDecoder;
    m_decoders[cobDecoder->extension()] = cobDecoder;
    m_decoders[objDecoder->extension()] = objDecoder;
    m_decoders[imgDecoder->extension()] = imgDecoder;
    m_decoders[bspDecoder->extension()] = bspDecoder;
}

ResourceMgr::~ResourceMgr()
{
}

sptr(Resource) ResourceMgr::getResource(const string &name)
{
    fs::path p(name);
    string fullpath;

    if (fs::is_directory(p))
        fullpath = fs::canonical(p).string();
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
                    rit = m_resources.find(fs::canonical(p).string());
                    if (rit != m_resources.end())
                    {
                        return rit->second;
                    }
                }
                catch (...) { }
            }

            // else -> find by name
            rit = std::find_if(m_resources.begin(), m_resources.end(),
                               [&](map<string, sptr(Resource) >::value_type &val)
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
//        syslog << error << resourcepath << "without extension" << logerr;
        return;
    }

    // ensure that we have decoder for this resource
    string extension = p.extension().string();
    if (extension.at(0) == '.')
    {
        extension.erase(extension.begin());
    }

    // skip config files
    if (extension == "yaml")
        return;

    auto dit = m_decoders.find(extension);

    if (dit == m_decoders.end())
    {
        syslog << error << resourcepath << "has unsupported file format." << logerr;
        return;
    }

    // if we already have the resource
    string fullpath;
    if (is_directory(p))
        fullpath = fs::canonical(p).string();
    else
        fullpath = p.string();

    auto rit = m_resources.find(fullpath);
    if (rit != m_resources.end())
    {
        syslog << error << resourcepath << "already loaded." << logwarn;
        return;
    }

    if (!fs::exists(fullpath))
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
catch (fs::filesystem_error &e)
{
    syslog << "Boost filesystem exception occurred:" << e.what() << logerr;
}

void ResourceMgr::unloadResource(const string &/*resourcepath*/)
{
    // TODO:
}

void ResourceMgr::loadAllResources() try
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

    syslog << "Loaded resources:\n";
    for (auto resource : m_resources)
    {
        syslog << resource.first << "with name" << resource.second->getName() << "\n";
    }
    syslog << logmess;
}
catch (fs::filesystem_error &e)
{
    syslog << "Boost filesystem exception occurred:" << e.what() << logerr;
}

void ResourceMgr::addPath(const string &name) try
{
    if (name.empty())
    {
        syslog << "Trying to add empty resources path" << logwarn;
        return;
    }

    using namespace fs;

    path p(name);

    if (exists(p))
    {
        if (is_directory(p))
        {
            // if this path isn't in container

            auto it = std::find_if(m_loadablePaths.begin(),
                                   m_loadablePaths.end(),
                                   [&](path &it){ return canonical(p).string() == canonical(it).string(); } );

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
catch (fs::filesystem_error &e)
{
    syslog << "Boost filesystem exception occurred:" << e.what() << logerr;
}

void ResourceMgr::listPath()
{
    syslog << "Path list:\n";
    for (auto p : m_loadablePaths)
        syslog << fs::canonical(p).string() << "\n";

    syslog << logdebug;
}

}
