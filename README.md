Raven
=====

A dynamic window manager forked from Suckless' [dwm](https://dwm.suckless.org/).
This exists simply to avoid conflicting with Debian's dwm package and because in 
time it will diverge even more significantly from upsteam, beyond applying simple
patches.

Layouts
-------

* Tile (classic Master/Stack)
* Right Master/Left Stack
* Bottom Stack
* Deck
* Monocle

Extra Features
--------------

* Gaps
* Layouts can be set per tag
* Adjustable status bar height
* More to come

Building Requirements
---------------------
In order to build Raven you need the Xlib header files.

A Debian package can be built by running the

```
debuild -i -us -uc -b
```

command, provided the __devscripts__ package is installed.

Installation
------------
Edit config.mk to match your local setup (Raven is installed into
the /usr namespace by default).

Afterwards enter the following command to build and install (if
necessary as root):

    make clean install


Running
-------
Add the following line to your .xinitrc to start Raven using startx:

    exec raven

In order to connect Raven to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec raven

(This will start raven on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec raven


Configuration
-------------
The configuration of Raven is done by creating a custom config.h
and (re)compiling the source code.

-------

#### _See LICENSE file for copyright and license details_
