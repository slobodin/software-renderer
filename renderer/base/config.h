/*
 * config.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "ospath.h"
#include "osfile.h"
#include "controller.h"

namespace base
{

class Config
{
    friend class Controller;
    Config();
    ~Config();

    void configure(const OsPath &path, Controller *controller);
};

}

#endif // CONFIG_H
