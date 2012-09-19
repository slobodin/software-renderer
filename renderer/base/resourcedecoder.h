/*
 * resourcedecoder.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RESOURCEDECODER_H
#define RESOURCEDECODER_H

#include "comm_pch.h"
#include "osfile.h"

namespace base
{

class Resource;

//! Abstract resource decoder.
/*!
  * We can simple support new assets types by creating
  * new class derived from ResourceDecoder.
  * All that we need is to implement decode() function, which
  * read and process file and translates file data to
  * inner renderer type representation.
  */
class ResourceDecoder
{
protected:
    //! Helper, that brings some abstraction.
    /*!
      * This function gets new line from a file.
      * Then calls user callback of type MyDecoder::fun(string &gettedLine),
      * and, if this line contains stopper, parseWhile ends.
      */
    template<typename T>
    void parseWhile(void (T::*lambda)(string &line), const string &stopper, TextFile &file);

public:
    //! Default ctor.
    ResourceDecoder() { }
    //! Dtor.
    virtual ~ResourceDecoder() { }

    //! Need to be implemented in derived classes. Creates engine representation of the asset.
    virtual sptr(Resource)  decode(const string &path) = 0;

    //! Returns asset extension.
    virtual string          extension() const = 0;
};

template<typename T>
void ResourceDecoder::parseWhile(void (T::*lambda)(string &line), const string &stopper, TextFile &file)
{
    string line;
    do
    {
        line = file.getLine();

        if (line.empty())
            continue;

        T *ptr = static_cast<T *>(this);

        (ptr->*lambda)(line);

        if (line.find(stopper) != string::npos)
            break;

        line.clear();

    } while (line.empty());
}

}

#endif // RESOURCEDECODER_H
