/*
 * main.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "unixapplication.h"

int main()
{
    UnixApplication app;
//    char *msg = "Hello, world!";

//    Display *d;
//    if ((d = XOpenDisplay(getenv("DISPLAY"))) == NULL)
//    {
//        std::cerr << "Can't connect to X Server";
//        return 1;
//    }

//    int s = DefaultScreen(d);

//    Window w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 200, 1, BlackPixel(d, s), WhitePixel(d, s));

//    XSelectInput(d, w, ExposureMask | KeyPressMask);

//    XMapWindow(d, w);

//    XEvent e;
//    while (true)
//    {
//        XNextEvent(d, &e);

//        if (e.type == Expose)
//        {
//            XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
//            XDrawString(d, w, DefaultGC(d, s), 50, 50, msg, strlen(msg));
//        }

//        if (e.type == KeyPress)
//            break;
//    }

//    XCloseDisplay(d);

    return 0;
}
