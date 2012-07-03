/*
 * resourcemgr.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RESOURCEMGR_H
#define RESOURCEMGR_H

#include "comm_pch.h"

namespace rend
{
class SceneObject;
}

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

    //! Gets the resource.
    /*!
      * Just returns the pointer to the resource, if resource is loaded.
      * Otherwise loads resource from the filesystem.
      * \return Pointer to the resource.
      * \param name Path to the asset or name of the resource.
      */
    sptr(Resource) getResource(const string &name);

    void loadResource(const string &resourcepath);
    void unloadResource(const string &resourcepath);

public:
    //! Default ctor.
    ResourceMgr();
    //! Dtor.
    ~ResourceMgr();

    // getMesh
    // getTexture
    // etc
    sptr(rend::SceneObject) getSceneObject(const string &name);

    void loadAllResources();

    void addPath(const string &name);
    void listPath();
};

}

#endif // RESOURCEMGR_H
