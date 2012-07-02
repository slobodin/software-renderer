/*
 * config.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "controller.h"
#include "resourcemgr.h"

namespace base
{

class Config
{
public:
    Config();
    ~Config();

    void configure(Controller *controller);
    void configure(ResourceMgr *rmgr);
};

}

#endif // CONFIG_H
