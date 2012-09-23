Here is simple software renderer. It means, that it doesn't use OpenGL or DirectX to perform rendering. 
All that it use is tk (gui library) functions to put image block on a screen (window).

Why software rendering?
========
Just educatonal and kind of research goals.

Features
========
Now it supports:
1) Loading some graphics files with mesh data(.obj, .cob, .asc). Also it can load bmp files.
2) Lighting (ambient, directional and point).
3) Constant, wireframe and flat shading.
4) Simple material support.
5) Mathematical operations with scene nodes like scaling, translating and rotation.
6) Customizable camera.
7) Configuration files (you can tune lights (intensity, position, etc) or add objects, that will appear in a scene). 
   Also you can setup position of objects through scene config file.

TODO: gouraud shading, textures and animation.

Usage
=====
Check out distr directory to get compiled examples (actually, one example).
wasd - move, mouse + left mouse button - cam control.

**Note**: resources need to be in the executable directory, 
or this dir may be passed explicitly to the renderer through command line.

for example:
$ ./client-tk ../../resources
Otherwise you'll get nothing.

Compile
=======
This software uses qmake build system (I'm using Qt creator) and have .pro files with qt-creator project description.
Also you need boost (at least 1.51), tk/tcl and CImg library.
Another libraries (cpptk and yamlcpp) included in project.
This renderer works well on Linux and Windows systems.

Package structure
===========
The main directory is organized as follows:

client-tk/ - test project, uses renderer library
dist/ - compiled binaries
example-1/ - project, that shows renderer features
resources/ - some mesh data and renderer config files (.yaml extention)
README - this file
software-renderer.pro - qt creator project

License
=======
This tool is provided under the MIT license.
