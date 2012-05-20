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
class OsPath;

DECLARE_EXCEPTION(UnsupportedResource)

//! Resource manager.
/*!
  * Contains all loaded assets.
  */
class ResourceMgr : boost::noncopyable
{
    map<string, sptr(Resource) > m_resources;
    map<string, sptr(ResourceDecoder) > m_decoders;

public:
    //! Default ctor.
    ResourceMgr();
    //! Dtor.
    ~ResourceMgr();
    
    //! Gets the resource.
    /*!
      * Just returns the pointer to resource, if resource is loaded.
      * Otherwise loads resource from the filesystem.
      * \return Pointer to the resource.
      * \param path Path to the asset.
      */
    sptr(Resource) getResource(const string &path);
    sptr(Resource) getResource(const OsPath &path);
};

}

#endif // RESOURCEMGR_H
