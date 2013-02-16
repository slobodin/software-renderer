**This file is outdate**

Here is simple software renderer. It means, that it doesn't use OpenGL or DirectX to perform rendering. 
All that it use is WinAPI functions to put image block on a screen.

Why software rendering?
========
Just educatonal and kind of research goals.

Features
========
Now it supports:
* Loading some graphics files with mesh data(.obj). Also it can load bmp files via CImg library.
* Lighting (ambient, directional and point).
* Constant, wireframe, flat and gouraud shading.
* Simple material support.
* Z buffer.
* Bilinear filtering for texture mapping.
* Mathematical operations with scene nodes like scaling, translating and rotation.
* Perspective correct texture mapping.
* Customizable camera.
* Configuration files (you can tune lights (intensity, position, etc) or add objects, that will appear in a scene). 
   Also you can setup position of objects through the scene config file.

**TODO**: optimization.

Usage
=====
Check out [this](https://github.com/flaming0/software-renderer/blob/master/www/example/soft-rend-win.zip?raw=true) to get compiled example.
Use wasd to perform camera movement, mouse + left mouse button - cam control.

Compile
=======
This renderer supports only Windows. In order to compile it you should use Visual Studio 2012 (the project uses C++11).

Package structure
===========
The main directory is organized as follows:

* client/ - project for library testing.
* renderer/ - main part: renderer code, that compiles into static library.
* resources/ - some mesh data and renderer config files (with .yaml extention).
* www/ - images for future wiki.
* README.md - this file.
* df3d.sln - MSVS2012 solution file.

Wiki
====
Is [here](https://github.com/flaming0/software-renderer/wiki). There you can see some screenshots.

License
=======
This tool is provided under the MIT license.
