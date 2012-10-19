//
// Copyright (C) 2004-2006, Maciej Sobczak
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

#ifndef CPPTK_H_INCLUDED
#define CPPTK_H_INCLUDED

#include "base/cpptkbase.h"


namespace Tk
{

// various Tk bits and pieces

// starter pieces (genuine Tk commands)

details_cpptk::Expr bell();

details_cpptk::Expr bindtags(std::string const &name,
     std::string const &tags = std::string());     

details_cpptk::Expr button(std::string const &name);

details_cpptk::Expr canvas(std::string const &name);

details_cpptk::Expr clipboard(std::string const &option);

details_cpptk::Expr clipboard(std::string const &option, std::string const &data);

details_cpptk::Expr destroy(std::string const &name);

details_cpptk::Expr entry(std::string const &name);

details_cpptk::Expr fonts(std::string const &option,
     std::string const &name = std::string());

details_cpptk::Expr grab(std::string const &option,
     std::string const &name = std::string());

details_cpptk::Expr images(std::string const &option,
     std::string const &tn = std::string(),
     std::string const &name = std::string());

details_cpptk::Expr label(std::string const &name);

details_cpptk::Expr labelframe(std::string const &name);

details_cpptk::Expr listbox(std::string const &name);

details_cpptk::Expr menu(std::string const &name);

details_cpptk::Expr menubutton(std::string const &name);

details_cpptk::Expr message(std::string const &name);

details_cpptk::Expr option(std::string const &todo,
     std::string const &s1 = std::string(),
     std::string const &s2 = std::string(),
     std::string const &s3 = std::string());

details_cpptk::Expr pack(std::string const &w1,
     std::string const &w2 = std::string(),
     std::string const &w3 = std::string(),
     std::string const &w4 = std::string(),
     std::string const &w5 = std::string(),
     std::string const &w6 = std::string(),
     std::string const &w7 = std::string(),
     std::string const &w8 = std::string(),
     std::string const &w9 = std::string(),
     std::string const &w10 = std::string());

template <typename T>
details_cpptk::Expr pack(std::string const &option,
     std::string const &w, T const &t)
{
     std::string str("pack ");
     str += option; str += " ";
     str += w; str += " ";
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr panedwindow(std::string const &name);

details_cpptk::Expr scale(std::string const &name);

details_cpptk::Expr scrollbar(std::string const &name);

details_cpptk::Expr spinbox(std::string const &name);

details_cpptk::Expr textw(std::string const &name);

details_cpptk::Expr tk_chooseColor();

details_cpptk::Expr tk_chooseDirectory();

details_cpptk::Expr tk_dialog(std::string const &window, std::string const &title,
     std::string const &text, std::string const &bitmap,
     std::string const &def, std::string const &but1,
     std::string const &but2 = std::string(),
     std::string const &but3 = std::string(),
     std::string const &but4 = std::string());

details_cpptk::Expr tk_focusNext(std::string const &window);

details_cpptk::Expr tk_focusPrev(std::string const &window);

details_cpptk::Expr tk_getOpenFile();

details_cpptk::Expr tk_getSaveFile();

details_cpptk::Expr tk_menuSetFocus(std::string const &menu);

details_cpptk::Expr tk_messageBox();

template <typename T, class InputIterator>
details_cpptk::Expr tk_optionMenu(std::string const &butname, T &var,
     InputIterator b, InputIterator e)
{
     std::string str("tk_optionMenu ");
     str += butname; str += " ";
     str += details_cpptk::addLinkVar(var);
     for (InputIterator i = b; i != e; ++i)
     {
          str += " \"";
          str += *i;
          str += '\"';
     }
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr tk_popup(std::string const &menu, T1 const &x, T2 const &y)
{
     std::string str("tk_popup ");
     str += menu; str += " ";
     str += details_cpptk::toString(x); str += " ";
     str += details_cpptk::toString(y);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr tk_popup(std::string const &menu, T1 const &x, T2 const &y,
     int entry)
{
     std::string str("tk_popup ");
     str += menu; str += " ";
     str += details_cpptk::toString(x); str += " ";
     str += details_cpptk::toString(y); str += " ";
     str += details_cpptk::toString(entry);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr tk_setPalette(std::string const &color);

details_cpptk::Expr tk_textCopy(std::string const &w);

details_cpptk::Expr tk_textCut(std::string const &w);

details_cpptk::Expr tk_textPaste(std::string const &w);

details_cpptk::Expr tkwait(std::string const &option, std::string const &w);

details_cpptk::Expr winfo(std::string const &option, std::string const &w);

template <typename T1, typename T2>
details_cpptk::Expr winfo(std::string const &option, T1 const &val1,
     T2 const &val2)
{
     std::string str("winfo ");
     str += option;
     std::string postfix(" ");
     postfix += details_cpptk::toString(val1);
     postfix += " ";
     postfix += details_cpptk::toString(val2);
     return details_cpptk::Expr(str, postfix);
}

details_cpptk::Expr wm(std::string const &option, std::string const &w);

template <typename T>
details_cpptk::Expr wm(std::string const &option, std::string const &w,
     T const &t)
{
     std::string str("wm ");
     str += option; str += " ";
     str += w; str += " \"";
     str += details_cpptk::toString(t);
     str += '\"';
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr wm(std::string const &option, std::string const &w,
     T1 const &t1, T2 const &t2)
{
     std::string str("wm ");
     str += option; str += " ";
     str += w; str += " \"";
     str += details_cpptk::toString(t1); str += "\" \"";
     str += details_cpptk::toString(t2); str += '\"';
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2, typename T3, typename T4>
details_cpptk::Expr wm(std::string const &option, std::string const &w,
     T1 const &t1, T2 const &t2, T3 const &t3, T4 const &t4)
{
     std::string str("wm ");
     str += option; str += " ";
     str += w; str += " \"";
     str += details_cpptk::toString(t1); str += "\" \"";
     str += details_cpptk::toString(t2); str += "\" \"";
     str += details_cpptk::toString(t3); str += "\" \"";
     str += details_cpptk::toString(t4); str += '\"';
     return details_cpptk::Expr(str);
}

details_cpptk::Expr wmprotocol(std::string const &w,
     std::string const &proto = std::string());

template <class Functor>
details_cpptk::Expr wmprotocol(std::string const &w,
     std::string const &proto, Functor f)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback0<Functor>(f)));

     std::string str("wm protocol ");
     str += w;          str += " ";
     str += proto;      str += " { ";
     str += newCmd;     str += " }";
     return details_cpptk::Expr(str);
}

// widget commands

template <typename T>
details_cpptk::Expr activate(T const &t)
{
     std::string str("activate ");
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr addtag(std::string const &tag, std::string const &spec);

template <typename T>
details_cpptk::Expr addtag(std::string const &tag, std::string const &spec,
     T const &arg)
{
     std::string str("addtag ");
     str += tag;    str += " ";
     str += spec;   str += " ";
     str += details_cpptk::toString(arg);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr addtag(std::string const &tag, std::string const &spec,
     T1 const &arg1, T2 const &arg2)
{
     std::string str("addtag ");
     str += tag;    str += " ";
     str += spec;   str += " ";
     str += details_cpptk::toString(arg1); str += " ";
     str += details_cpptk::toString(arg2);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2, typename T3>
details_cpptk::Expr addtag(std::string const &tag, std::string const &spec,
     T1 const &arg1, T2 const &arg2, T3 const &arg3)
{
     std::string str("addtag ");
     str += tag;    str += " ";
     str += spec;   str += " ";
     str += details_cpptk::toString(arg1);    str += " ";
     str += details_cpptk::toString(arg2);    str += " ";
     str += details_cpptk::toString(arg3);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2, typename T3, typename T4>
details_cpptk::Expr addtag(std::string const &tag, std::string const &spec,
     T1 const &arg1, T2 const &arg2, T3 const &arg3, T4 const &arg4)
{
     std::string str("addtag ");
     str += tag;    str += " ";
     str += spec;   str += " ";
     str += details_cpptk::toString(arg1);    str += " ";
     str += details_cpptk::toString(arg2);    str += " ";
     str += details_cpptk::toString(arg3);    str += " ";
     str += details_cpptk::toString(arg4);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr blank();

template <typename T>
details_cpptk::Expr canvasx(T const &x)
{
     std::string str("canvasx ");
     str += details_cpptk::toString(x);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr canvasx(T1 const &x, T2 const &g)
{
     std::string str("canvasx ");
     str += details_cpptk::toString(x); str += " ";
     str += details_cpptk::toString(g);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr canvasy(T const &y)
{
     std::string str("canvasy ");
     str += details_cpptk::toString(y);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr canvasy(T1 const &y, T2 const &g)
{
     std::string str("canvasy ");
     str += details_cpptk::toString(y); str += " ";
     str += details_cpptk::toString(g);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr clone(std::string const &newpath,
     std::string const &type = std::string());

details_cpptk::Expr compare(std::string const &indx1, std::string const &oper,
     std::string const &indx2);

details_cpptk::Expr coords();

template <typename T>
details_cpptk::Expr coords(T const &t)
{
     std::string str("coords ");
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr coords(std::string const &item, int x, int y);

details_cpptk::Expr coords(std::string const &item, Point const &p);

details_cpptk::Expr coords(std::string const &item, int x1, int y1, int x2, int y2);

details_cpptk::Expr coords(std::string const &item,
     Point const &p1, Point const &p2);

details_cpptk::Expr coords(std::string const &item, Box const &b);

template <class InputIterator>
details_cpptk::Expr coords(std::string const &item,
     InputIterator b, InputIterator e)
{
     std::string cmd("coords ");
     cmd += item;
     if (b == e)
     {
          throw TkError("A non-empty list of coordinates expected");
     }
     for (InputIterator i = b; i != e; ++i)
     {
          cmd += ' ';
          cmd += details_cpptk::toString(*i);
     }
     
     return details_cpptk::Expr(cmd);
}

details_cpptk::Expr copy(std::string const &photo);

details_cpptk::Expr curselection();

template <typename T>
details_cpptk::Expr dchars(std::string const &item, T const &first)
{
     std::string str("dchars ");
     str += item;   str += " ";
     str += details_cpptk::toString(first);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr dchars(std::string const &item,
     T1 const &first, T2 const &last)
{
     std::string str("dchars ");
     str += item;   str += " ";
     str += details_cpptk::toString(first); str += " ";
     str += details_cpptk::toString(last);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr debug();
details_cpptk::Expr debug(bool d);

template <typename T>
details_cpptk::Expr deleteentry(T const &t)
{
     std::string str("delete ");
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr deleteentry(T1 const &t1, T2 const &t2)
{
     std::string str("delete ");
     str += details_cpptk::toString(t1); str += " ";
     str += details_cpptk::toString(t2);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr deleteitem(T const &t)
{
     std::string str("delete ");
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

template <class InputIterator>
details_cpptk::Expr deleteitem(InputIterator b, InputIterator e)
{
     std::string cmd("delete");
     for (InputIterator i = b; i != e; ++i)
     {
          cmd += ' ';
          cmd += *i;
     }
     
     return details_cpptk::Expr(cmd);
}

template <typename T>
details_cpptk::Expr deletetext(T const &t)
{
     std::string str("delete ");
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr deletetext(T1 const &t1, T2 const &t2)
{
     std::string str("delete ");
     str += details_cpptk::toString(t1); str += " ";
     str += details_cpptk::toString(t2);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr delta(T1 const &t1, T2 const &t2)
{
     std::string str("delta ");
     str += details_cpptk::toString(t1); str += " ";
     str += details_cpptk::toString(t2);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr deselect();

details_cpptk::Expr dlineinfo(std::string const &indx);

details_cpptk::Expr dtag(std::string const &tag,
     std::string const &todel = std::string());

details_cpptk::Expr dump(std::string const &indx1,
     std::string const &indx2 = std::string());

details_cpptk::Expr edit(std::string const &option);

template <typename T>
details_cpptk::Expr edit(std::string const &option, T const &t)
{
     std::string str("edit ");
     str += option; str += " ";
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr entrycget(T const &index, std::string const &option)
{
     std::string str("entrycget ");
     str += details_cpptk::toString(index); str += " -";
     str += option;
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr entryconfigure(T const &index)
{
     std::string str("entryconfigure ");
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr find(std::string const &spec);

template <typename T1>
details_cpptk::Expr find(std::string const &spec, T1 const &arg1)
{
     std::string str("find ");
     str += spec;   str += " ";
     str += details_cpptk::toString(arg1);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr find(std::string const &spec, T1 const &arg1, T2 const &arg2)
{
     std::string str("find ");
     str += spec;   str += " ";
     str += details_cpptk::toString(arg1); str += " ";
     str += details_cpptk::toString(arg2);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2, typename T3>
details_cpptk::Expr find(std::string const &spec,
     T1 const &arg1, T2 const &arg2, T3 const &arg3)
{
     std::string str("find ");
     str += spec;   str += " ";
     str += details_cpptk::toString(arg1); str += " ";
     str += details_cpptk::toString(arg2); str += " ";
     str += details_cpptk::toString(arg3);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2, typename T3, typename T4>
details_cpptk::Expr find(std::string const &spec,
     T1 const &arg1, T2 const &arg2, T3 const &arg3, T4 const &arg4)
{
     std::string str("find ");
     str += spec;   str += " ";
     str += details_cpptk::toString(arg1); str += " ";
     str += details_cpptk::toString(arg2); str += " ";
     str += details_cpptk::toString(arg3); str += " ";
     str += details_cpptk::toString(arg4);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr flash();

template <typename T1, typename T2>
details_cpptk::Expr fraction(T1 const &t1, T2 const &t2)
{
     std::string str("fraction ");
     str += details_cpptk::toString(t1); str += " ";
     str += details_cpptk::toString(t2);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr getsize();

details_cpptk::Expr gettags(std::string const &item);

template <typename T>
details_cpptk::Expr icursor(T const &index)
{
     std::string str("icursor ");
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr icursor(std::string const &item, T const &index)
{
     std::string str("icursor ");
     str += item;   str += " ";
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr identify(T1 const &x, T2 const &y)
{
     std::string str("identify ");
     str += details_cpptk::toString(x); str += " ";
     str += details_cpptk::toString(y);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr index(T const &index)
{
     std::string str("index ");
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr index(std::string const &item, T const &index)
{
     std::string str("index ");
     str += item;   str += " ";
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr insert(T const &index, std::string const &what)
{
     std::string str("insert ");
     str += details_cpptk::toString(index); str += " \"";
     str += details_cpptk::quote(what);   str += "\"";
     return details_cpptk::Expr(str);
}

details_cpptk::Expr insert(std::string const &index,
     std::string const &txt, std::string const &tag = std::string());

template <typename T>
details_cpptk::Expr insert(std::string const &item, T const &index,
     std::string const &what)
{
     std::string str("insert ");
     str += item;   str += " ";
     str += details_cpptk::toString(index); str += " \"";
     str += details_cpptk::quote(what);   str += "\"";
     return details_cpptk::Expr(str);
}

template <int N>
details_cpptk::Expr insert(std::string const &indx, char const txt[N],
     std::string const &tag)
{
     std::string str("insert ");
     str += indx;   str += " \"";
     str += details_cpptk::quote(txt); str += "\" ";
     str += tag;
     return details_cpptk::Expr(str);
}

template <typename T, class InputIterator>
details_cpptk::Expr insert(T const &index, InputIterator b, InputIterator e)
{
     std::string str("insert ");
     str += details_cpptk::toString(index);
     for (InputIterator i = b; i != e; ++i)
     {
          str += " \"";
          str += details_cpptk::toString(*i);
          str += '\"';
     }
     return details_cpptk::Expr(str);
}

details_cpptk::Expr invoke();

template <typename T>
details_cpptk::Expr invoke(T const &index)
{
     std::string str("invoke ");
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr itemcget(T const &t, std::string const &name)
{
     std::string str("itemcget ");
     str += details_cpptk::toString(t); str += " -";
     str += name;
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr itemconfigure(T const &t)
{
     std::string str("itemconfigure ");
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr move(std::string const &item, int x, int y);

template <typename T>
details_cpptk::Expr nearest(T const &t)
{
     std::string str("nearest ");
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr panecget(std::string const &w, std::string const &option);

details_cpptk::Expr paneconfigure(std::string const &w);

details_cpptk::Expr panes();

template <typename T1, typename T2>
details_cpptk::Expr post(T1 const &x, T2 const &y)
{
     std::string str("post ");
     str += details_cpptk::toString(x); str += " ";
     str += details_cpptk::toString(y);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr postcascade(T const &index)
{
     std::string str("postcascade ");
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr postscript();

details_cpptk::Expr proxy(std::string const &option);

template <typename T1, typename T2>
details_cpptk::Expr proxy(std::string const &option, T1 const &x, T2 const &y)
{
     std::string str("proxy ");
     str += option; str += " ";
     str += details_cpptk::toString(x); str += " ";
     str += details_cpptk::toString(y);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr put(std::string const &color);

details_cpptk::Expr read(std::string const &file);

details_cpptk::Expr redither();

details_cpptk::Expr sash(std::string const &option, int index);

template <typename T1, typename T2>
details_cpptk::Expr sash(std::string const &option, int index,
     T1 const &x, T2 const &y)
{
     std::string str("sash ");
     str += option; str += " ";
     str += details_cpptk::toString(index); str += " ";
     str += details_cpptk::toString(x); str += " ";
     str += details_cpptk::toString(y);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr scale(std::string const &item,
     T1 const &xorig, T2 const &yorig, double xscale, double yscale)
{
     std::string str("scale ");
     str += item;     str += " ";
     str += details_cpptk::toString(xorig); str += " ";
     str += details_cpptk::toString(yorig); str += " ";
     str += details_cpptk::toString(xscale); str += " ";
     str += details_cpptk::toString(yscale);
     return details_cpptk::Expr(str);
}

template <typename T>
details_cpptk::Expr scan(std::string const &option, T const &x)
{
     std::string str("scan ");
     str += option; str += " ";
     str += details_cpptk::toString(x);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr scan(std::string const &option,
     T1 const &x, T2 const &y)
{
     std::string str("scan ");
     str += option; str += " ";
     str += details_cpptk::toString(x); str += " ";
     str += details_cpptk::toString(y);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr scan(std::string const &option,
     T1 const &x, T2 const &y, double gain)
{
     std::string str("scan ");
     str += option; str += " ";
     str += details_cpptk::toString(x); str += " ";
     str += details_cpptk::toString(y); str += " ";
     str += details_cpptk::toString(gain);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr search(std::string const &pattern,
     std::string const &indx1, std::string const &indx2 = std::string());

template <typename T>
details_cpptk::Expr see(T const &t)
{
     std::string str("see ");
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr select();
details_cpptk::Expr select(std::string const &option);

template <typename T>
details_cpptk::Expr select(std::string const &option,
     std::string const &item, T const &index)
{
     std::string str("select ");
     str += option; str += " ";
     str += item; str += " ";
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr selection(std::string const &option);

template <typename T>
details_cpptk::Expr selection(std::string const &option, T const &index)
{
     std::string str("selection ");
     str += option; str += " ";
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

template <typename T1, typename T2>
details_cpptk::Expr selection(std::string const &option, T1 const &i1, T2 const &i2)
{
     std::string str("selection ");
     str += option; str += " ";
     str += details_cpptk::toString(i1); str += " ";
     str += details_cpptk::toString(i2);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr tag(std::string const &option,
     std::string const &tagname = std::string());

details_cpptk::Expr tag(std::string const &option, std::string const &tagname,
     std::string const &indx1, std::string const &indx2 = std::string());

details_cpptk::Expr tag(std::string const &option, std::string const &tagname,
     std::string const &indx1, char const *indx2);

template <class Functor>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback0<Functor>(f)));

     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback1<Functor,
                    typename EventAttr1::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1, class EventAttr2>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1, EventAttr2 const &ea2)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback2<Functor,
                    typename EventAttr1::attrType,
                    typename EventAttr2::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " ";
     str += ea2.get();  str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1, class EventAttr2,
     class EventAttr3>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback3<Functor,
                    typename EventAttr1::attrType,
                    typename EventAttr2::attrType,
                    typename EventAttr3::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " ";
     str += ea2.get();  str += " ";
     str += ea3.get();  str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1, class EventAttr2,
     class EventAttr3, class EventAttr4>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
     EventAttr4 const &ea4)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback4<Functor,
                    typename EventAttr1::attrType,
                    typename EventAttr2::attrType,
                    typename EventAttr3::attrType,
                    typename EventAttr4::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " ";
     str += ea2.get();  str += " ";
     str += ea3.get();  str += " ";
     str += ea4.get();  str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1, class EventAttr2,
     class EventAttr3, class EventAttr4, class EventAttr5>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
     EventAttr4 const &ea4, EventAttr5 const &ea5)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback5<Functor,
                    typename EventAttr1::attrType,
                    typename EventAttr2::attrType,
                    typename EventAttr3::attrType,
                    typename EventAttr4::attrType,
                    typename EventAttr5::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " ";
     str += ea2.get();  str += " ";
     str += ea3.get();  str += " ";
     str += ea4.get();  str += " ";
     str += ea5.get();  str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1, class EventAttr2,
     class EventAttr3, class EventAttr4, class EventAttr5, class EventAttr6>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
     EventAttr4 const &ea4, EventAttr5 const &ea5, EventAttr6 const &ea6)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback6<Functor,
                    typename EventAttr1::attrType,
                    typename EventAttr2::attrType,
                    typename EventAttr3::attrType,
                    typename EventAttr4::attrType,
                    typename EventAttr5::attrType,
                    typename EventAttr6::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " ";
     str += ea2.get();  str += " ";
     str += ea3.get();  str += " ";
     str += ea4.get();  str += " ";
     str += ea5.get();  str += " ";
     str += ea6.get();  str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1, class EventAttr2,
     class EventAttr3, class EventAttr4, class EventAttr5, class EventAttr6,
     class EventAttr7>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
     EventAttr4 const &ea4, EventAttr5 const &ea5, EventAttr6 const &ea6,
     EventAttr7 const &ea7)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback7<Functor,
                    typename EventAttr1::attrType,
                    typename EventAttr2::attrType,
                    typename EventAttr3::attrType,
                    typename EventAttr4::attrType,
                    typename EventAttr5::attrType,
                    typename EventAttr6::attrType,
                    typename EventAttr7::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " ";
     str += ea2.get();  str += " ";
     str += ea3.get();  str += " ";
     str += ea4.get();  str += " ";
     str += ea5.get();  str += " ";
     str += ea6.get();  str += " ";
     str += ea7.get();  str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1, class EventAttr2,
     class EventAttr3, class EventAttr4, class EventAttr5, class EventAttr6,
     class EventAttr7, class EventAttr8>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
     EventAttr4 const &ea4, EventAttr5 const &ea5, EventAttr6 const &ea6,
     EventAttr7 const &ea7, EventAttr8 const &ea8)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback8<Functor,
                    typename EventAttr1::attrType,
                    typename EventAttr2::attrType,
                    typename EventAttr3::attrType,
                    typename EventAttr4::attrType,
                    typename EventAttr5::attrType,
                    typename EventAttr6::attrType,
                    typename EventAttr7::attrType,
                    typename EventAttr8::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " ";
     str += ea2.get();  str += " ";
     str += ea3.get();  str += " ";
     str += ea4.get();  str += " ";
     str += ea5.get();  str += " ";
     str += ea6.get();  str += " ";
     str += ea7.get();  str += " ";
     str += ea8.get();  str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1, class EventAttr2,
     class EventAttr3, class EventAttr4, class EventAttr5, class EventAttr6,
     class EventAttr7, class EventAttr8, class EventAttr9>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
     EventAttr4 const &ea4, EventAttr5 const &ea5, EventAttr6 const &ea6,
     EventAttr7 const &ea7, EventAttr8 const &ea8, EventAttr9 const &ea9)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback9<Functor,
                    typename EventAttr1::attrType,
                    typename EventAttr2::attrType,
                    typename EventAttr3::attrType,
                    typename EventAttr4::attrType,
                    typename EventAttr5::attrType,
                    typename EventAttr6::attrType,
                    typename EventAttr7::attrType,
                    typename EventAttr8::attrType,
                    typename EventAttr9::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " ";
     str += ea2.get();  str += " ";
     str += ea3.get();  str += " ";
     str += ea4.get();  str += " ";
     str += ea5.get();  str += " ";
     str += ea6.get();  str += " ";
     str += ea7.get();  str += " ";
     str += ea8.get();  str += " ";
     str += ea9.get();  str += " }";
     return details_cpptk::Expr(str);
}

template <class Functor, class EventAttr1, class EventAttr2,
     class EventAttr3, class EventAttr4, class EventAttr5, class EventAttr6,
     class EventAttr7, class EventAttr8, class EventAttr9, class EventAttr10>
details_cpptk::Expr tag(std::string const &option, std::string const &name,
     std::string const &seq, Functor f,
     EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
     EventAttr4 const &ea4, EventAttr5 const &ea5, EventAttr6 const &ea6,
     EventAttr7 const &ea7, EventAttr8 const &ea8, EventAttr9 const &ea9,
     EventAttr10 const &ea10)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback10<Functor,
                    typename EventAttr1::attrType,
                    typename EventAttr2::attrType,
                    typename EventAttr3::attrType,
                    typename EventAttr4::attrType,
                    typename EventAttr5::attrType,
                    typename EventAttr6::attrType,
                    typename EventAttr7::attrType,
                    typename EventAttr8::attrType,
                    typename EventAttr9::attrType,
                    typename EventAttr10::attrType>(f)));
     
     std::string str("tag ");
     str += option;     str += " ";
     str += name;       str += " ";
     str += seq;        str += " { ";
     str += newCmd;     str += " ";
     str += ea1.get();  str += " ";
     str += ea2.get();  str += " ";
     str += ea3.get();  str += " ";
     str += ea4.get();  str += " ";
     str += ea5.get();  str += " ";
     str += ea6.get();  str += " ";
     str += ea7.get();  str += " ";
     str += ea8.get();  str += " ";
     str += ea9.get();  str += " ";
     str += ea10.get(); str += " }";
     return details_cpptk::Expr(str);
}

details_cpptk::Expr toggle();

details_cpptk::Expr transparency(std::string const &option, int x, int y);
details_cpptk::Expr transparency(std::string const &option, int x, int y, bool tr);

details_cpptk::Expr windows(std::string const &option,
     std::string const &indx = std::string(),
     std::string const &name = std::string());

details_cpptk::Expr write(std::string const &file);

details_cpptk::Expr xview();

template <typename T>
details_cpptk::Expr xview(T const &t)
{
     std::string str("xview ");
     str += details_cpptk::toString(t);
     return details_cpptk::Expr(str);
}
details_cpptk::Expr xview(std::string const &option, double fraction);
details_cpptk::Expr xview(std::string const option,
     int number, std::string const &what);

template <typename T>
details_cpptk::Expr yposition(T const &index)
{
     std::string str("yposition ");
     str += details_cpptk::toString(index);
     return details_cpptk::Expr(str);
}

details_cpptk::Expr yview();
details_cpptk::Expr yview(std::string const &option, double fraction);
details_cpptk::Expr yview(std::string const option,
     int number, std::string const &what);

// options

#define CPPTK_OPTION(name, quote) extern details_cpptk::Option name;
#include "cpptkoptions.x"
#undef CPPTK_OPTION

// other options, requiring special syntax or compilation

template <typename T1, typename T2, typename T3>
details_cpptk::Expr arrowshape(T1 const &t1, T2 const &t2, T3 const &t3)
{
     std::string str(" -arrowshape {");
     str += details_cpptk::toString(t1); str += " ";
     str += details_cpptk::toString(t2); str += " ";
     str += details_cpptk::toString(t3); str += "}";
     return details_cpptk::Expr(str, false);
}

details_cpptk::Expr backwards();

// instead of conflicting 'type'
details_cpptk::Expr cliptype(std::string const &type);

details_cpptk::Expr count(int &i);

details_cpptk::Expr count(std::string const &name);

details_cpptk::Expr defaultbutton(std::string const &but);

details_cpptk::Expr defaultstate(std::string const &name);

details_cpptk::Expr exact();

details_cpptk::Expr filetypes(std::string const &types);

details_cpptk::Expr forwards();

details_cpptk::Expr grayscale();

template <class Functor> details_cpptk::Expr invalidcommand(Functor f)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback0<Functor>(f)));
     
     std::string str(" -invalidcommand ");
     str += newCmd;
     return details_cpptk::Expr(str, false);
}

details_cpptk::Expr invalidcommand(char const *name);
details_cpptk::Expr invalidcommand(std::string const &name);

class CallbackHandle;
details_cpptk::Expr invalidcommand(CallbackHandle const &handle);

template <class Functor> details_cpptk::Expr postcommand(Functor f)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback0<Functor>(f)));
     
     std::string str(" -postcommand ");
     str += newCmd;
     return details_cpptk::Expr(str, false);
}

details_cpptk::Expr menutype(std::string const &type);

details_cpptk::Expr messagetext(std::string const &txt);

details_cpptk::Expr messagetype(std::string const &type);

details_cpptk::Expr multiple();

details_cpptk::Expr nocase();

details_cpptk::Expr postcommand(std::string const &name);

class CallbackHandle;
details_cpptk::Expr postcommand(CallbackHandle const &handle);

details_cpptk::Expr regexp();

template <typename T1, typename T2, typename T3, typename T4>
details_cpptk::Expr scrollregion(T1 const &x1, T2 const &y1,
     T3 const &x2, T4 const y2)
{
     std::string str(" -scrollregion ");
     str += details_cpptk::toString(x1); str += " ";
     str += details_cpptk::toString(y1); str += " ";
     str += details_cpptk::toString(x2); str += " ";
     str += details_cpptk::toString(y2);
     return details_cpptk::Expr(str, false);
}

details_cpptk::Expr shrink();

details_cpptk::Expr submenu(std::string const &menu);

details_cpptk::Expr subsample(int x, int y);

details_cpptk::Expr tags();

template <class InputIterator>
details_cpptk::Expr tags(InputIterator b, InputIterator e)
{
     std::string cmd(" -tags {");
     for (InputIterator i = b; i != e; ++i)
     {
          cmd += ' ';
          cmd += *i;
     }
     cmd += "}";
     
     return details_cpptk::Expr(cmd, false);
}

template <class Functor> details_cpptk::Expr tearoffcommand(Functor f)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback0<Functor>(f)));
     
     std::string str(" -tearoffcommand ");
     str += newCmd;
     return details_cpptk::Expr(str, false);
}

details_cpptk::Expr tearoffcommand(std::string const &name);

class CallbackHandle;
details_cpptk::Expr tearoffcommand(CallbackHandle const &handle);

template <typename T>
details_cpptk::Expr textvariable(T &t)
{
     std::string str(" -textvariable ");
     str += details_cpptk::addLinkVar(t);
     return details_cpptk::Expr(str, false);
}

details_cpptk::Expr textvariable(std::string const &name);

template <class Functor>
details_cpptk::Expr validatecommand(Functor f)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback0<Functor>(f)));
     
     std::string str(" -validatecommand ");
     str += newCmd;
     return details_cpptk::Expr(str, false);
}

template <class Functor, class ValidateAttr1>
details_cpptk::Expr validatecommand(Functor f, ValidateAttr1 const &va1)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback1<Functor,
                    typename ValidateAttr1::validType>(f)));
     
     std::string str(" -validatecommand { ");
     str += newCmd;     str += " ";
     str += va1.get();  str += " }";
     return details_cpptk::Expr(str, false);
}

template <class Functor, class ValidateAttr1, class ValidateAttr2>
details_cpptk::Expr validatecommand(Functor f, ValidateAttr1 const &va1,
     ValidateAttr2 const &va2)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback2<Functor,
                    typename ValidateAttr1::validType,
                    typename ValidateAttr2::validType>(f)));
     
     std::string str(" -validatecommand { ");
     str += newCmd;     str += " ";
     str += va1.get();  str += " ";
     str += va2.get();  str += " }";
     return details_cpptk::Expr(str, false);
}

template <class Functor, class ValidateAttr1, class ValidateAttr2,
     class ValidateAttr3>
details_cpptk::Expr validatecommand(Functor f, ValidateAttr1 const &va1,
     ValidateAttr2 const &va2, ValidateAttr3 const &va3)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback3<Functor,
                    typename ValidateAttr1::validType,
                    typename ValidateAttr2::validType,
                    typename ValidateAttr3::validType>(f)));
     
     std::string str(" -validatecommand { ");
     str += newCmd;     str += " ";
     str += va1.get();  str += " ";
     str += va2.get();  str += " ";
     str += va3.get();  str += " }";
     return details_cpptk::Expr(str, false);
}

template <class Functor, class ValidateAttr1, class ValidateAttr2,
     class ValidateAttr3, class ValidateAttr4>
details_cpptk::Expr validatecommand(Functor f, ValidateAttr1 const &va1,
     ValidateAttr2 const &va2, ValidateAttr3 const &va3,
     ValidateAttr4 const &va4)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback4<Functor,
                    typename ValidateAttr1::validType,
                    typename ValidateAttr2::validType,
                    typename ValidateAttr3::validType,
                    typename ValidateAttr4::validType>(f)));
     
     std::string str(" -validatecommand { ");
     str += newCmd;     str += " ";
     str += va1.get();  str += " ";
     str += va2.get();  str += " ";
     str += va3.get();  str += " ";
     str += va4.get();  str += " }";
     return details_cpptk::Expr(str, false);
}

template <class Functor, class ValidateAttr1, class ValidateAttr2,
     class ValidateAttr3, class ValidateAttr4, class ValidateAttr5>
details_cpptk::Expr validatecommand(Functor f, ValidateAttr1 const &va1,
     ValidateAttr2 const &va2, ValidateAttr3 const &va3,
     ValidateAttr4 const &va4, ValidateAttr5 const &va5)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback5<Functor,
                    typename ValidateAttr1::validType,
                    typename ValidateAttr2::validType,
                    typename ValidateAttr3::validType,
                    typename ValidateAttr4::validType,
                    typename ValidateAttr5::validType>(f)));
     
     std::string str(" -validatecommand { ");
     str += newCmd;     str += " ";
     str += va1.get();  str += " ";
     str += va2.get();  str += " ";
     str += va3.get();  str += " ";
     str += va4.get();  str += " ";
     str += va5.get();  str += " }";
     return details_cpptk::Expr(str, false);
}

template <class Functor, class ValidateAttr1, class ValidateAttr2,
     class ValidateAttr3, class ValidateAttr4, class ValidateAttr5,
     class ValidateAttr6>
details_cpptk::Expr validatecommand(Functor f, ValidateAttr1 const &va1,
     ValidateAttr2 const &va2, ValidateAttr3 const &va3,
     ValidateAttr4 const &va4, ValidateAttr5 const &va5,
     ValidateAttr6 const &va6)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback6<Functor,
                    typename ValidateAttr1::validType,
                    typename ValidateAttr2::validType,
                    typename ValidateAttr3::validType,
                    typename ValidateAttr4::validType,
                    typename ValidateAttr5::validType,
                    typename ValidateAttr6::validType>(f)));
     
     std::string str(" -validatecommand { ");
     str += newCmd;     str += " ";
     str += va1.get();  str += " ";
     str += va2.get();  str += " ";
     str += va3.get();  str += " ";
     str += va4.get();  str += " ";
     str += va5.get();  str += " ";
     str += va6.get();  str += " }";
     return details_cpptk::Expr(str, false);
}

template <class Functor, class ValidateAttr1, class ValidateAttr2,
     class ValidateAttr3, class ValidateAttr4, class ValidateAttr5,
     class ValidateAttr6, class ValidateAttr7>
details_cpptk::Expr validatecommand(Functor f, ValidateAttr1 const &va1,
     ValidateAttr2 const &va2, ValidateAttr3 const &va3,
     ValidateAttr4 const &va4, ValidateAttr5 const &va5,
     ValidateAttr6 const &va6, ValidateAttr7 const &va7)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback7<Functor,
                    typename ValidateAttr1::validType,
                    typename ValidateAttr2::validType,
                    typename ValidateAttr3::validType,
                    typename ValidateAttr4::validType,
                    typename ValidateAttr5::validType,
                    typename ValidateAttr6::validType,
                    typename ValidateAttr7::validType>(f)));
     
     std::string str(" -validatecommand { ");
     str += newCmd;     str += " ";
     str += va1.get();  str += " ";
     str += va2.get();  str += " ";
     str += va3.get();  str += " ";
     str += va4.get();  str += " ";
     str += va5.get();  str += " ";
     str += va6.get();  str += " ";
     str += va7.get();  str += " }";
     return details_cpptk::Expr(str, false);
}

template <class Functor, class ValidateAttr1, class ValidateAttr2,
     class ValidateAttr3, class ValidateAttr4, class ValidateAttr5,
     class ValidateAttr6, class ValidateAttr7, class ValidateAttr8>
details_cpptk::Expr validatecommand(Functor f, ValidateAttr1 const &va1,
     ValidateAttr2 const &va2, ValidateAttr3 const &va3,
     ValidateAttr4 const &va4, ValidateAttr5 const &va5,
     ValidateAttr6 const &va6, ValidateAttr7 const &va7,
     ValidateAttr8 const &va8)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback8<Functor,
                    typename ValidateAttr1::validType,
                    typename ValidateAttr2::validType,
                    typename ValidateAttr3::validType,
                    typename ValidateAttr4::validType,
                    typename ValidateAttr5::validType,
                    typename ValidateAttr6::validType,
                    typename ValidateAttr7::validType,
                    typename ValidateAttr8::validType>(f)));
     
     std::string str(" -validatecommand { ");
     str += newCmd;     str += " ";
     str += va1.get();  str += " ";
     str += va2.get();  str += " ";
     str += va3.get();  str += " ";
     str += va4.get();  str += " ";
     str += va5.get();  str += " ";
     str += va6.get();  str += " ";
     str += va7.get();  str += " ";
     str += va8.get();  str += " }";
     return details_cpptk::Expr(str, false);
}

template <typename T>
details_cpptk::Expr variable(T &t)
{
     std::string str(" -variable ");
     str += details_cpptk::addLinkVar(t);
     return details_cpptk::Expr(str, false);
}

details_cpptk::Expr variable(std::string const &name);

details_cpptk::Expr zoom(double x, double y);

// event attribute specifiers

extern details_cpptk::EventAttr<std::string> event_A; // %A - character
extern details_cpptk::EventAttr<int>         event_b; // %b - button number
extern details_cpptk::EventAttr<int>         event_D; // %D - delta for mouse wheel
extern details_cpptk::EventAttr<int>         event_f; // %f - focus flag
extern details_cpptk::EventAttr<int>         event_h; // %h - height
extern details_cpptk::EventAttr<std::string> event_k; // %k - keycode
extern details_cpptk::EventAttr<std::string> event_K; // %K - keysym
extern details_cpptk::EventAttr<std::string> event_m; // %m - mode
extern details_cpptk::EventAttr<int>         event_N; // %N - keysym, numeric value
extern details_cpptk::EventAttr<std::string> event_s; // %s - state
extern details_cpptk::EventAttr<std::string> event_T; // %T - type
extern details_cpptk::EventAttr<int>         event_w; // %w - width
extern details_cpptk::EventAttr<std::string> event_W; // %W - window name
extern details_cpptk::EventAttr<int>         event_x; // %x - x coordinate
extern details_cpptk::EventAttr<int>         event_X; // %X - root x coordinate
extern details_cpptk::EventAttr<int>         event_y; // %x - y coordinate
extern details_cpptk::EventAttr<int>         event_Y; // %Y - root y coordinate

extern details_cpptk::ValidateAttr<int>         valid_d; // %d - type of action
extern details_cpptk::ValidateAttr<int>         valid_i; // %i - index of char
extern details_cpptk::ValidateAttr<std::string> valid_P; // %P - new value
extern details_cpptk::ValidateAttr<std::string> valid_s; // %s - current value
extern details_cpptk::ValidateAttr<std::string> valid_S; // %S - diff
extern details_cpptk::ValidateAttr<std::string> valid_v; // %v - curr. type of val.
extern details_cpptk::ValidateAttr<std::string> valid_V; // %V - type of trigger
extern details_cpptk::ValidateAttr<std::string> valid_W; // %W - name of entry

// constants

#define CPPTK_CONSTANT(c) extern char const * c;
#include "cpptkconstants.x"
#undef CPPTK_CONSTANT

// additional constants

extern char const *deletefont; // instead of conflicting 'delete'
extern char const *deleteimg;  // instead of conflicting 'delete'
extern char const *deletetag;  // instead of conflicting 'delete'
extern char const *setglobal;
extern char const *wrapchar;   // instead of conflicting 'char'
extern char const *wrapword;   // for consistency

// additional functions

template <class Functor>
details_cpptk::Expr afteridle(Functor f)
{
     std::string newCmd = details_cpptk::addCallback(
          boost::shared_ptr<details_cpptk::CallbackBase>(
               new details_cpptk::Callback0<Functor>(f)));

     std::string str("after idle ");
     str += newCmd;
     return details_cpptk::Expr(str);
}

details_cpptk::Expr afteridle(std::string const &cmd);

details_cpptk::Expr update(std::string const &option = std::string());

// multi-purpose tokens
// these are tokens which are meant to be both commands
// and constants or options

namespace details_cpptk
{

class BindToken : public BasicToken
{
public:
     BindToken();
     
     Expr operator()(std::string const &name,
          std::string const &seq) const;

     template <class Functor>
     details_cpptk::Expr operator()(std::string const &name,
          std::string const &seq, Functor f) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback0<Functor>(f)));

          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback1<Functor,
                         typename EventAttr1::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1, class EventAttr2>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1, EventAttr2 const &ea2) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback2<Functor,
                         typename EventAttr1::attrType,
                         typename EventAttr2::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " ";
          str += ea2.get();  str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1, class EventAttr2,
          class EventAttr3>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1, EventAttr2 const &ea2,
          EventAttr3 const &ea3) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback3<Functor,
                         typename EventAttr1::attrType,
                         typename EventAttr2::attrType,
                         typename EventAttr3::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " ";
          str += ea2.get();  str += " ";
          str += ea3.get();  str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1, class EventAttr2,
          class EventAttr3, class EventAttr4>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
          EventAttr4 const &ea4) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback4<Functor,
                         typename EventAttr1::attrType,
                         typename EventAttr2::attrType,
                         typename EventAttr3::attrType,
                         typename EventAttr4::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " ";
          str += ea2.get();  str += " ";
          str += ea3.get();  str += " ";
          str += ea4.get();  str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1, class EventAttr2,
          class EventAttr3, class EventAttr4, class EventAttr5>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
          EventAttr4 const &ea4, EventAttr5 const &ea5) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback5<Functor,
                         typename EventAttr1::attrType,
                         typename EventAttr2::attrType,
                         typename EventAttr3::attrType,
                         typename EventAttr4::attrType,
                         typename EventAttr5::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " ";
          str += ea2.get();  str += " ";
          str += ea3.get();  str += " ";
          str += ea4.get();  str += " ";
          str += ea5.get();  str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1, class EventAttr2,
          class EventAttr3, class EventAttr4, class EventAttr5,
          class EventAttr6>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
          EventAttr4 const &ea4, EventAttr5 const &ea5,
          EventAttr6 const &ea6) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback6<Functor,
                         typename EventAttr1::attrType,
                         typename EventAttr2::attrType,
                         typename EventAttr3::attrType,
                         typename EventAttr4::attrType,
                         typename EventAttr5::attrType,
                         typename EventAttr6::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " ";
          str += ea2.get();  str += " ";
          str += ea3.get();  str += " ";
          str += ea4.get();  str += " ";
          str += ea5.get();  str += " ";
          str += ea6.get();  str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1, class EventAttr2,
          class EventAttr3, class EventAttr4, class EventAttr5,
          class EventAttr6, class EventAttr7>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
          EventAttr4 const &ea4, EventAttr5 const &ea5, EventAttr6 const &ea6,
          EventAttr7 const &ea7) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback7<Functor,
                         typename EventAttr1::attrType,
                         typename EventAttr2::attrType,
                         typename EventAttr3::attrType,
                         typename EventAttr4::attrType,
                         typename EventAttr5::attrType,
                         typename EventAttr6::attrType,
                         typename EventAttr7::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " ";
          str += ea2.get();  str += " ";
          str += ea3.get();  str += " ";
          str += ea4.get();  str += " ";
          str += ea5.get();  str += " ";
          str += ea6.get();  str += " ";
          str += ea7.get();  str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1, class EventAttr2,
          class EventAttr3, class EventAttr4, class EventAttr5,
          class EventAttr6, class EventAttr7, class EventAttr8>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
          EventAttr4 const &ea4, EventAttr5 const &ea5, EventAttr6 const &ea6,
          EventAttr7 const &ea7, EventAttr8 const &ea8) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback8<Functor,
                         typename EventAttr1::attrType,
                         typename EventAttr2::attrType,
                         typename EventAttr3::attrType,
                         typename EventAttr4::attrType,
                         typename EventAttr5::attrType,
                         typename EventAttr6::attrType,
                         typename EventAttr7::attrType,
                         typename EventAttr8::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " ";
          str += ea2.get();  str += " ";
          str += ea3.get();  str += " ";
          str += ea4.get();  str += " ";
          str += ea5.get();  str += " ";
          str += ea6.get();  str += " ";
          str += ea7.get();  str += " ";
          str += ea8.get();  str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1, class EventAttr2,
          class EventAttr3, class EventAttr4, class EventAttr5,
          class EventAttr6, class EventAttr7, class EventAttr8,
          class EventAttr9>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
          EventAttr4 const &ea4, EventAttr5 const &ea5, EventAttr6 const &ea6,
          EventAttr7 const &ea7, EventAttr8 const &ea8,
          EventAttr9 const &ea9) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback9<Functor,
                         typename EventAttr1::attrType,
                         typename EventAttr2::attrType,
                         typename EventAttr3::attrType,
                         typename EventAttr4::attrType,
                         typename EventAttr5::attrType,
                         typename EventAttr6::attrType,
                         typename EventAttr7::attrType,
                         typename EventAttr8::attrType,
                         typename EventAttr9::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " ";
          str += ea2.get();  str += " ";
          str += ea3.get();  str += " ";
          str += ea4.get();  str += " ";
          str += ea5.get();  str += " ";
          str += ea6.get();  str += " ";
          str += ea7.get();  str += " ";
          str += ea8.get();  str += " ";
          str += ea9.get();  str += " }";
          return Expr(str);
     }

     template <class Functor, class EventAttr1, class EventAttr2,
          class EventAttr3, class EventAttr4, class EventAttr5,
          class EventAttr6, class EventAttr7, class EventAttr8,
          class EventAttr9, class EventAttr10>
     Expr operator()(std::string const &name,
          std::string const &seq, Functor f,
          EventAttr1 const &ea1, EventAttr2 const &ea2, EventAttr3 const &ea3,
          EventAttr4 const &ea4, EventAttr5 const &ea5, EventAttr6 const &ea6,
          EventAttr7 const &ea7, EventAttr8 const &ea8, EventAttr9 const &ea9,
          EventAttr10 const &ea10) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback10<Functor,
                         typename EventAttr1::attrType,
                         typename EventAttr2::attrType,
                         typename EventAttr3::attrType,
                         typename EventAttr4::attrType,
                         typename EventAttr5::attrType,
                         typename EventAttr6::attrType,
                         typename EventAttr7::attrType,
                         typename EventAttr8::attrType,
                         typename EventAttr9::attrType,
                         typename EventAttr10::attrType>(f)));
     
          std::string str("bind ");
          str += name;       str += " ";
          str += seq;        str += " { ";
          str += newCmd;     str += " ";
          str += ea1.get();  str += " ";
          str += ea2.get();  str += " ";
          str += ea3.get();  str += " ";
          str += ea4.get();  str += " ";
          str += ea5.get();  str += " ";
          str += ea6.get();  str += " ";
          str += ea7.get();  str += " ";
          str += ea8.get();  str += " ";
          str += ea9.get();  str += " ";
          str += ea10.get(); str += " }";
          return Expr(str);
     }
};

class CheckButtonToken : public BasicToken
{
public:
     CheckButtonToken();
     Expr operator()(std::string const &name) const;
};

class FrameToken : public BasicToken
{
public:
     FrameToken();
     Expr operator()(std::string const &name) const;
};

class GridToken : public BasicToken
{
public:
     GridToken();
     Expr operator()(std::string const &option,
          std::string const &name) const;

     template <typename T>
     Expr operator()(std::string const &option,
          std::string const &name, T const &t) const
     {
          std::string str("grid ");
          str += option; str += " ";
          str += name; str += " ";
          str += toString(t);
          return Expr(str);
     }

     Expr operator()(std::string const &option,
          std::string const &name, int x, int y) const;
     Expr operator()(std::string const &option,
          std::string const &name,
          int col1, int row1, int col2, int row2) const;
};

class LowerToken : public BasicToken
{
public:
     LowerToken();
     Expr operator()(std::string const &name,
          std::string const &belowthis = std::string()) const;
};

class PlaceToken : public BasicToken
{
public:
     PlaceToken();
     Expr operator()(std::string const &w) const;
     Expr operator()(std::string const &option,
          std::string const &w) const;
};

class RadioButtonToken : public BasicToken
{
public:
     RadioButtonToken();
     Expr operator()(std::string const &name) const;
};

class RaiseToken : public BasicToken
{
public:
     RaiseToken();
     Expr operator()(std::string const &name,
          std::string const &abovethis = std::string()) const;
};

class ToplevelToken : public BasicToken
{
public:
     ToplevelToken();
     Expr operator()(std::string const &w) const;
};

class AddToken : public BasicToken
{
public:
     AddToken();
     Expr operator()(std::string const &tn) const;
};

class BboxToken : public BasicToken
{
public:
     BboxToken();
     
     template <typename T>
     Expr operator()(T const &t) const
     {
          std::string str("bbox ");
          str += toString(t);
          return Expr(str);
     }

     template <class InputIterator>
     Expr operator()(InputIterator b, InputIterator e) const
     {
          std::string cmd("bbox");
          if (b == e)
          {
               cmd += " {}";
          }
          for (InputIterator i = b; i != e; ++i)
          {
               cmd += ' ';
               cmd += *i;
          }
     
          return Expr(cmd);
     }
};

class CgetToken : public BasicToken
{
public:
     CgetToken();
     Expr operator()(std::string const &name) const;
};

class ConfigureToken : public BasicToken
{
public:
     ConfigureToken();
     Expr operator()() const;
};

class CreateToken : public BasicToken
{
public:
     CreateToken();
     
     Expr operator()(std::string const &type, int x, int y) const;

     Expr operator()(std::string const &type, Point const &p) const;

     Expr operator()(std::string const &type,
          int x1, int y1, int x2, int y2) const;

     Expr operator()(std::string const &type,
          Point const &p1, Point const &p2) const;

     Expr operator()(std::string const &type, Box const &b) const;

     template <class InputIterator>
     Expr operator()(std::string const &type,
          InputIterator b, InputIterator e) const
     {
          std::string cmd("create ");
          cmd += type;
          if (b == e)
          {
               throw TkError("A non-empty list of coordinates expected");
          }
          for (InputIterator i = b; i != e; ++i)
          {
               cmd += ' ';
               cmd += toString(*i);
          }
     
          return Expr(cmd);
     }
};

class FocusToken : public BasicToken
{
public:
     FocusToken();
     Expr operator()(std::string const &name = std::string()) const;
};

class ForgetToken : public BasicToken
{
public:
     ForgetToken();
     Expr operator()(std::string const &name) const;
};

class GetToken : public BasicToken
{
public:
     GetToken();
     Expr operator()() const;

     template <typename T>
     Expr operator()(T const &t) const
     {
          std::string str("get ");
          str += toString(t);
          return Expr(str);
     }

     template <typename T1, typename T2>
     Expr operator()(T1 const &t1, T2 const &t2) const
     {
          std::string str("get ");
          str += toString(t1); str += " ";
          str += toString(t2);
          return Expr(str);
     }
};

class MoveToToken : public BasicToken
{
public:
     MoveToToken();
     Expr operator()(double fraction) const;
};

class ScrollToken : public BasicToken
{
public:
     ScrollToken();
     Expr operator()(int n, std::string const &what) const;
};

class SetToken : public BasicToken
{
public:
     SetToken();

     Expr operator()() const;
     
     template <typename T>
     Expr operator()(T const &t) const
     {
          std::string str("set ");
          str += toString(t);
          return Expr(str);
     }
     
     Expr operator()(double first, double last) const;
};

class TypeToken : public BasicToken
{
public:
     TypeToken();
     
     template <typename T>
     Expr operator()(T const &item) const
     {
          std::string str("type ");
          str += toString(item);
          return Expr(str);
     }
};

class ValidateToken : public BasicToken
{
public:
     ValidateToken();
     Expr operator()() const;
     Expr operator()(std::string const &when) const;
};

class AllToken : public BasicToken
{
public:
     AllToken();
     Expr operator()() const;
};

class CommandToken : public BasicToken
{
public:
     CommandToken();
     
     template <class Functor> Expr operator()(Functor f) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback0<Functor>(f)));
     
          std::string str(" -command ");
          str += newCmd;
          return Expr(str, false);
     }

     Expr operator()(std::string const &name) const;
     Expr operator()(CallbackHandle const &handle) const;
};

class ElideToken : public BasicToken
{
public:
     ElideToken();
     Expr operator()() const;
     Expr operator()(bool b) const;
};

class FromToken : public BasicToken
{
public:
     FromToken();
     Expr operator()(int v) const;
     Expr operator()(int x1, int y1, int x2, int y2) const;
};

class ImageToken : public BasicToken
{
public:
     ImageToken();
     Expr operator()() const;
     Expr operator()(std::string const &name) const;
};

class MarkToken : public BasicToken
{
public:
     MarkToken();
     Expr operator()() const;
     Expr operator()(std::string const &option,
          std::string const &markname = std::string(),
          std::string const &dir = std::string()) const;
};

class MenuLabelToken : public BasicToken
{
public:
     MenuLabelToken();
     Expr operator()(std::string const &label) const;
};

class TextToken : public BasicToken
{
public:
     TextToken();
     Expr operator()() const;
     Expr operator()(std::string const &t) const;
};

class ToToken : public BasicToken
{
public:
     ToToken();
     Expr operator()(int val) const;
     Expr operator()(int x, int y) const;
     Expr operator()(int x1, int y1, int x2, int y2) const;
};

class WindowToken : public BasicToken
{
public:
     WindowToken();
     Expr operator()(std::string const &name = std::string()) const;
};

class WndClassToken : public BasicToken
{
public:
     WndClassToken();
     Expr operator()(std::string const &name) const;
};

class AfterToken : public BasicToken
{
public:
     AfterToken();
     Expr operator()(int time) const;
     Expr operator()(std::string const &name) const;
     Expr operator()(int time, std::string const &name) const;
     Expr operator()(std::string const &option, std::string const &id) const;

     template <class Functor>
     Expr operator()(int t, Functor f) const
     {
          std::string newCmd = addCallback(
               boost::shared_ptr<CallbackBase>(
                    new Callback0<Functor>(f)));

          std::string str("after ");
          str += toString(t); str += " ";
          str += newCmd;
          return Expr(str);
     }
};

class RGBToken : public BasicToken
{
public:
     RGBToken();
     std::string operator()(int r, int g, int b) const;
};

} // namespace details

extern details_cpptk::BindToken bind;
extern details_cpptk::CheckButtonToken checkbutton;
extern details_cpptk::FrameToken frame;
extern details_cpptk::GridToken grid;
extern details_cpptk::LowerToken lower;
extern details_cpptk::PlaceToken place;
extern details_cpptk::RadioButtonToken radiobutton;
extern details_cpptk::RaiseToken raise;
extern details_cpptk::ToplevelToken toplevel;
extern details_cpptk::AddToken add;
extern details_cpptk::BboxToken bbox;
extern details_cpptk::CgetToken cget;
extern details_cpptk::ConfigureToken configure;
extern details_cpptk::CreateToken create;
extern details_cpptk::FocusToken focus;
extern details_cpptk::ForgetToken forget;
extern details_cpptk::GetToken get;
extern details_cpptk::MoveToToken moveto;
extern details_cpptk::ScrollToken scroll;
extern details_cpptk::SetToken set;
extern details_cpptk::TypeToken type;
extern details_cpptk::ValidateToken validate;
extern details_cpptk::AllToken all;
extern details_cpptk::CommandToken command;
extern details_cpptk::ElideToken elide;
extern details_cpptk::FromToken from;
extern details_cpptk::ImageToken image;
extern details_cpptk::MarkToken mark;
extern details_cpptk::MenuLabelToken menulabel;
extern details_cpptk::TextToken text;
extern details_cpptk::ToToken to;
extern details_cpptk::WindowToken window;
extern details_cpptk::WndClassToken wndclass;
extern details_cpptk::AfterToken after;
extern details_cpptk::RGBToken rgb;

// helper functions

// for the '@x' coordinate notation
template <typename T>
std::string at(T const &t)
{
     std::string str("@");
     str += details_cpptk::toString(t);
     return str;
}

// for the '@x,y' coordinate notation
template <typename T1, typename T2>
std::string at(T1 const &t1, T2 const &t2)
{
     std::string str("@");
     str += details_cpptk::toString(t1); str += ",";
     str += details_cpptk::toString(t2);
     return str;
}

// for text widget coordinates
template <typename T1, typename T2>
std::string txt(T1 const &t1, T2 const &t2)
{
     std::string str;
     str += details_cpptk::toString(t1); str += ".";
     str += details_cpptk::toString(t2);
     return str;
}

} // namespace Tk

#endif // CPPTK_H_INCLUDED
