/*
 * resource.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#include "comm_pch.h"

namespace base
{

//! Abstract base for resources, that can be loaded.
/*!
  *
  */
class Resource : boost::noncopyable
{
protected:
    //! Name of the resource.
    string m_name;

public:
    //! Default ctor.
    Resource()
        : m_name("Unnamed")
    { }
    //! Dtor.
    virtual ~Resource()
    { }

    //! Sets the name.
    void    setName(const string &name) { m_name = name; }
    //! Gets the name.
    string  getName() const { return m_name; }
};

}

#endif // RESOURCE_H
