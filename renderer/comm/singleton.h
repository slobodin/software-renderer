/*
 * singleton.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include "comm_pch.h"

namespace common
{

//! Singleton class
template <class T>
class Singleton
{
protected:
    static T *m_instance;

public:
    Singleton()
    {
        assert(!m_instance);
        m_instance = static_cast<T *>(this);
    }

    virtual ~Singleton()
    {
        assert(m_instance);
        m_instance = 0;
    }

    static T &instance()
    {
        assert(m_instance);
        return *m_instance;
    }

    static T *ptr()
    {
        assert(m_instance);
        return m_instance;
    }

    static bool initialized()
    {
        return m_instance != 0;
    }
};

template <class T>
T *Singleton<T>::m_instance = 0;

}

#endif // SINGLETON_H
