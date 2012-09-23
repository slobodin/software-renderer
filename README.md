Here is simple software renderer. It means, that it doesn't use OpenGL or DirectX to perform rendering. 
All that it use is tk (gui library) functions to put image block on a screen (window).

Why software rendering?
========
Just educatonal and kind of research goals.

Features
========
Now it supports:
* Loading some graphics files with mesh data(.obj, .cob, .asc). Also it can load bmp files.
* Lighting (ambient, directional and point).
* Constant, wireframe and flat shading.
* Simple material support.
* Mathematical operations with scene nodes like scaling, translating and rotation.
* Customizable camera.
* Configuration files (you can tune lights (intensity, position, etc) or add objects, that will appear in a scene). 
   Also you can setup position of objects through scene config file.

TODO: gouraud shading, textures and animation.

Usage
=====
Check out distr directory to get compiled examples (actually, one example).
Use wasd to  perform camera moving, mouse + left mouse button - cam control.

**Note**: resources need to be in the executable directory, 
or this dir may be passed explicitly to the renderer through command line.
For example: $ ./client-tk ../../resources
Otherwise you'll get nothing.

Compile
=======
This renderer works well on Linux and Windows systems because it uses qmake build system. It has .pro files with qt creator project description.
Also you need boost (at least 1.51), tk/tcl (ActiveTcl for Windows) and CImg library.
Another libraries (cpptk and yamlcpp) included in project.
On Windows you also should set BOOST_ROOT and TCL_ROOT environment variables (for example, in Qt creator "build environment" tab)

Package structure
===========
The main directory is organized as follows:

* client-tk/ - test project, uses renderer library
* dist/ - compiled binaries
* example-1/ - project, that shows renderer features
* renderer/ - main part: renderer code, that compiles into static library.
* resources/ - some mesh data and renderer config files (.yaml extention)
* www/ - images for future wiki.
* README - this file
* software-renderer.pro - qt creator project

License
=======
This tool is provided under the MIT license.
