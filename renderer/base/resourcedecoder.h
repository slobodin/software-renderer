/*
 * resourcedecoder.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RESOURCEDECODER_H
#define RESOURCEDECODER_H

#include "comm_pch.h"

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

}

#endif // RESOURCEDECODER_H
