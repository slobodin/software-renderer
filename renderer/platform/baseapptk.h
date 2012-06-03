/*
 * baseapptk.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef BASEAPPTK_H
#define BASEAPPTK_H

#include "baseapp.h"
#include "viewport.h"

class ViewportTkImage : public rend::Viewport
{
    string m_widgetName;

public:
    ViewportTkImage(const string &widgetName);

    void flush(unsigned char *pixels);
};

class BaseAppTk : public BaseApp
{
public:
    BaseAppTk(char *argv[]);
    ~BaseAppTk();

    void run();
};

#endif // BASEAPPTK_H
