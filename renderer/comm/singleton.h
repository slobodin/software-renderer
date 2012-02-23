#ifndef SINGLETON_H
#define SINGLETON_H

#include "comm_pch.h"

namespace common
{

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

    ~Singleton()
    {
        assert(m_instance);
        m_instance = nullptr;
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
        return m_instance != nullptr;;
    }
};

template <class T>
T *Singleton<T>::m_instance = nullptr;

}

#endif // SINGLETON_H
