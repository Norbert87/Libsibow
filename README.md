===============================================
Libsibow: a Simple C++ library for Bag of Words
===============================================
Norberto Madueño Galan and Manuel J. Marin-Jimenez

This library implements a Bag of Words (BOW) model. You can
use this library to train and test object models in a simple way.

--------------------------------------------------------------------------------

   Source-Code:   https://github.com/Norbert87/Libsibow

--------------------------------------------------------------------------------
Contents of the package:
--------------------------------------------------------------------------------
- include: headers of the library (.h)
- src: source files of the library (.cpp)
- tests: sample programs using libsibow

--------------------------------------------------------------------------------
Installation
--------------------------------------------------------------------------------
Download the latest source code from GitHub.
This software requires OpenCV 2.4.x.
CMake is highly recommended.

--------------------------------------------------------------------------------
Quick start
--------------------------------------------------------------------------------
Let us assume that the root directory of libsibow is named ‘rootdir’.
Open a terminal, and type in the command line the following instructions:
```
1) cd <rootdir>
2) mkdir build
3) cd build
4) cmake ..
5) make
6) make install   (You might need to do sudo if your are in an Unix-like system)
```
If everything went well, both the library and test programs should have been
created into <rootdir>/build subdirectories.


--------------------------------------------------------------------------------
Documentation
--------------------------------------------------------------------------------
You can build the documentation of the library with Doxygen.


--------------------------------------------------------------------------------
Contact
--------------------------------------------------------------------------------

You can contact the authors of this software at:
https://github.com/Norbert87
mjmarin <at> uco <dot> es

--------------------------------------------------------------------------------
Version history
--------------------------------------------------------------------------------
- 1.0: initial release
