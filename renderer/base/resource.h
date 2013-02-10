/*
 * resource.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef RESOURCE_H
#define RESOURCE_H

namespace base
{

class ResourceMgr;

//! Abstract base for resources, that can be loaded.
/*!
  *
  */
class Resource
{
protected:
    //! Name of the resource.
    std::string m_name;

public:
    //! Default ctor.
    Resource()
        : m_name("Unnamed")
    { }
    //! Dtor.
    virtual ~Resource()
    { }

    //! Sets the name.
    void    setName(const std::string &name) { m_name = name; }
    //! Gets the name.
    std::string  getName() const { return m_name; }

    virtual void additionalLoading(ResourceMgr * const /*rm*/) { }

    NONCOPYABLE(Resource)
};

}

#endif // RESOURCE_H
