/*
 * ospath.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef OSPATH_H
#define OSPATH_H

#include "comm_pch.h"

namespace base
{

// TODO: replace with boost::filesystem

//! Simple directory path wrapper.
/*!
  *
  */
class OsPath
{
    //! Path to the file.
    string m_path;
    //! File extention.
    string m_extention;

    // helper
    void parse();
public:
    //! Constructs OsPath from std::string class.
    OsPath(const string &path);
    //! Constructs OsPath from C-string.
    OsPath(const char *path);

    //! Dtor.
    ~OsPath() { }

    //! Gets file extention.
    string fileExtention() const;
    //! Gets full path to the file. (now NOT FULL ^^)
    string filePath() const;
    //! Is empty?
    bool empty() const;
};

}

#endif // OSPATH_H
