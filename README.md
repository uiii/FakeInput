FakeInput library
=================

FakeInput is user input simulation library. It provides API to programaticaly
generate input events from input devices such as keyboard and mouse. 
Also you can use it to execute any external programs.

It is written in C++ and ported to Unix-like and Windows platforms.

Author
------

Richard Jedlička (uiii.dev@gmail.com)

Requirements
------------

To succesfully build this library you need this:

- [CMake](http://www.cmake.org/) build system

Unix-like platform only:

- [pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config)
- [Xlib](http://en.wikipedia.org/wiki/Xlib) library
- XTest extension of Xlib

If you want to build also test applications, you need this:

- [Qt 4](http://qt.nokia.com/) framework

If you want to generate API documentation, you need this:

- [Doxygen](http://www.stack.nl/~dimitri/doxygen/) documentation system

Download
--------

You can use [Git](http://git-scm.com):

    $ git clone https://uiii@github.com/uiii/FakeInput.git

or you can download the archive

[.tar.gz](https://github.com/uiii/FakeInput/tarball/master)

[.zip](https://github.com/uiii/FakeInput/zipball/master)

Build
-----

1. Open your console (on _Unix-like platform_) or _Visual Studio command prompt_ (on _Windows_).

2. Go to _FakeInput_'s root and make build directory:

        $ cd FakeInput && mkdir build && cd build

3. Now generate files needed to build:

        $ cmake ../

4. Compile:

    On _Unix-like platform_ run:

        $ make
            
    On _Windows_ (see _Notes_):

        > msbuild FakeInput.sln /p:Configuration=Release

    Now the **compiled library** is in the `bin/lib` directory.

* If you want to build **test applications** run _CMake_ in 3. step with option `-DTEST_APP=ON`.
Test applications will be in the `bin/test` directory.

* If you want to generate **API documentation** run _CMake_ in 3. step with option `-DDOC=ON`.
Generated documentation will be in the `doc` directory.

Install
-------

Default path where to install the library is `/usr/local` on _Unix-like platform_ and
`C:\Program Files\FakeInput` on _Windows_. To specify another **installation location**
run _CMake_ in the 3. step of _Build_ section with option `-DINSTALL_PREFIX=path/where/to/install`

On _Unix-like platform_ run:

    $ make install

On _Windows_ (see _Notes_):

    > msbuild INSTALL.vcxproj /p:Configuration=Release

Uninstall
---------

On _Unix-like platform_ run:

    $ make uninstall

On _Windows_ (see _Notes_):

    > msbuild uninstall.vcxproj

This will remove all files and directories that were created during install.

Notes
-----

Appropriate command depends on the generator you set to _CMake_ (see [generator-documentation]),
by default it is _Visual Studio_ project file.

[generator-documentation]: http://www.cmake.org/cmake/help/cmake-2-8-docs.html#opt:-Ggenerator-name
