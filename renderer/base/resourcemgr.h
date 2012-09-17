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

    /*!
      * Returns asset (by name or path) from resource contatiner.
      * For example, mesh, texture, scene object
      */
    template<typename T>
    sptr(T) getObject(const string &name);

    void loadAllResources();

    void addPath(const string &name);
    void listPath();
};

template<typename T>
sptr(T) ResourceMgr::getObject(const string &name)
{
    sptr(T) nullobj;

    sptr(Resource) newResource = getResource(name);
    if (newResource)
    {
        if (boost::dynamic_pointer_cast<T>(newResource))
            return boost::dynamic_pointer_cast<T>(newResource);
        else
            return nullobj;
    }
    else
        return nullobj;
}

}

#endif // RESOURCEMGR_H
