/*
 * resourcemgr.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef RESOURCEMGR_H
#define RESOURCEMGR_H

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
class ResourceMgr
{
    typedef std::tr2::sys::path FSPath;
    std::vector<FSPath> m_loadablePaths;

    std::map<std::string, sptr(Resource) >        m_resources;
    std::map<std::string, sptr(ResourceDecoder) > m_decoders;

    //! Gets the resource.
    /*!
      * Just returns the pointer to the resource, if resource is loaded.
      * Otherwise loads resource from the filesystem.
      * \return Pointer to the resource.
      * \param name Path to the asset or name of the resource.
      */
    sptr(Resource) getResource(const std::string &name);

    void loadResource(const std::string &resourcepath);
    void unloadResource(const std::string &resourcepath);

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
    sptr(T) getObject(const std::string &name);

    void loadAllResources();

    void addPath(const std::string &name);
    void listPath();

    NONCOPYABLE(ResourceMgr)
};

template<typename T>
sptr(T) ResourceMgr::getObject(const std::string &name)
{
    sptr(T) nullobj;

    sptr(Resource) newResource = getResource(name);
    if (newResource)
    {
//        if (boost::dynamic_pointer_cast<)

        if (std::tr1::dynamic_pointer_cast<T>(newResource))
            return std::tr1::dynamic_pointer_cast<T>(newResource);
        else
            return nullobj;
    }
    else
        return nullobj;
}

}

#endif // RESOURCEMGR_H
