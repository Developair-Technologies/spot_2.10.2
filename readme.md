SPOT Custom
========

Spot is a model-checking toolkit originally hosted at: https://spot.lrde.epita.fr/
Please refer to their gitlab page and website for further documentation. 

This repo contains a custom version of spot with some minor tweaks. 

Fast Startup
============

You should not need to read further than this section. Please download and install the .deb package from:

    link to non-existent website because i need David's help

That's it. 

Building
========

You should build your version only if you have a *very* *good* *reason*. 

Local Usage
-----------

To build the package, please use: 
    ./configure --prefix ~/usr
    make
    make install
Note that the make install step is required, otherwise Developair packages that depend on this version of spot will break.

To check that the tools are correctly installed, run:
    ltl2tgba --version
If your shell reports that ltl2tgba is not found, add ~/usr/bin to you $PATH environment variable or check that your user (that shall not be root) has permission to access that folder.

Deployement
-----------

Building is nice and stuff, but it takes time. Conveniently, we can make a debian package.
