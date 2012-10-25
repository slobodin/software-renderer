Here is simple software renderer. It means, that it doesn't use OpenGL or DirectX to perform rendering (although, it's not a big problem to change software renderer with opengl). 
All that it use is tk gui library functions to put image block on a screen (window).

Why software rendering?
========
Just educatonal and kind of research goals.

Features
========
Now it supports:
* Loading some graphics files with mesh data(.obj, .cob, .asc). Also it can load bmp files.
* Lighting (ambient, directional and point).
* Constant, wireframe, flat and gouraud shading.
* Simple material support.
* Z buffer.
* Mathematical operations with scene nodes like scaling, translating and rotation.
* Perspective correct texture mapping.
* Customizable camera.
* Configuration files (you can tune lights (intensity, position, etc) or add objects, that will appear in a scene). 
   Also you can setup position of objects through the scene config file.

**TODO**: animation, optimization.

Usage
=====
Check out [this](https://github.com/downloads/flaming0/software-renderer/soft-rend-win.zip) to get compiled examples, or 
[this](https://github.com/downloads/flaming0/software-renderer/soft-ren-linux.tar.gz) for Linux version.
Use wasd to perform camera movement, mouse + left mouse button - cam control.
On windows version you need to install tcl/tk binaries.

**Note**: resources need to be in the executable directory, 
or this dir may be passed explicitly to the renderer through command line.
For example: $ ./client-tk ../../resources
Otherwise you'll get nothing.

Compile
=======
This renderer works well on Linux and Windows systems because it uses qmake build system. It has .pro files with qt creator project description.
Also you need boost (at least 1.51), tk/tcl (ActiveTcl for Windows) ang Google test library (gtest).
Another libraries (cpptk, yamlcpp and easybmp) included in the project.
On Windows you also should set BOOST_ROOT and TCL_ROOT environment variables (for example, via Qt creator "build environment" tab)

Note, that project uses C++11, thus you need appropriate compiler (I use gcc on Linux and mingw on Windows).

Package structure
===========
The main directory is organized as follows:

* client-tk/ - project for library testing.
* example-1/ - project, that shows renderer features.
* example-2/ - example of texture mapping, flat shading and movable point light.
* example-3/ - example of terrain rendering.
* renderer/ - main part: renderer code, that compiles into static library.
* resources/ - some mesh data and renderer config files (with .yaml extention).
* www/ - images for future wiki.
* README.md - this file.
* software-renderer.pro - qt creator project.

Wiki
====
Is [here](https://github.com/flaming0/software-renderer/wiki). There you can see some screenshots.

License
=======
This tool is provided under the MIT license.
