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

First of all, creating the debian package requires more stuff than just building the software. Please note that the working directory MUST BE CLEAN like the butt of a baby:

    git clean -f

This will remove all untracked files and changes.
From the main folder, run:

    sudo ./developair/install_build_dep.sh

Note the the "sudo" part is important. The script checks it and will return ERR_CODE 126 if it is not ran as sudo. This will install most dependencies in your debian-based distro. It'll also add a line to `/etc/apt/sources.list`. Subsequent calls to this script will add the same line again. 

Then, please run:

    ./configure --prefix ~/usr --disable-python

After this step, all errors require a fresh start from the repo (`git clean -f`is your friend).
Now please cross all your fingers, legs, hands, arms, hair and ask someone (your hands should not be able to type anything since they're crossed) to type:

    sudo make deb
    
This is configured to stop on errors, so anything wrong will stop the process. `git clean -f`is still your friend, and you can fix the problem and start over from the config step. 
