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

/**
  * Abstract base for resources, that can be loaded.
  */
class Resource
{
protected:
    string m_name;

public:
    Resource()
        : m_name("Unnamed")
    { }
    virtual ~Resource() { }

    void setName(const string &name) { m_name = name; }
    string name() const { return m_name; }
};

}

#endif // RESOURCE_H
