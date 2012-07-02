/*
 * resourcemgr.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RESOURCEMGR_H
#define RESOURCEMGR_H

#include "comm_pch.h"

namespace base
{

class Resource;
class ResourceDecoder;

DECLARE_EXCEPTION(UnsupportedResource)

//! Resource manager.
/*!
  * Contains all loaded assets.
  */
class ResourceMgr : boost::noncopyable
{
    vector<path> m_loadablePaths;

    map<string, sptr(Resource) >        m_resources;
    map<string, sptr(ResourceDecoder) > m_decoders;

public:
    //! Default ctor.
    ResourceMgr();
    //! Dtor.
    ~ResourceMgr();
    
    //! Gets the resource.
    /*!
      * Just returns the pointer to the resource, if resource is loaded.
      * Otherwise loads resource from the filesystem.
      * \return Pointer to the resource.
      * \param path Path to the asset.
      */
    sptr(Resource) getResource(const string &resourcepath);

    // getMesh
    // getTexture
    // etc

    void loadResource(const string &resourcepath);
    void unloadResource(const string &resourcepath);

    void loadResources();

    void addPath(const string &name);
    void listPath();
};

}

#endif // RESOURCEMGR_H
