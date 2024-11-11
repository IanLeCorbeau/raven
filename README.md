# Raven

Raven is a fork of Suckless' [dwm](https://dwm.suckless.org/).
For details, see the manual page.

## Building a deb package

Because Raven is a simple program, `equivs-build` is used to build
the deb package, rather than the traditional `debuild` command.

Before building, ensure that the following packages are installed:

* equivs
* libx11-dev
* libxinerama-dev
* libxft-dev
* libfreetype6-dev

Then, from Raven's directory, run (as a non-root user):

```
$ make deb
```

## Build/Install Manually

In order to build Raven you need the Xlib header files.


### Installation

Edit config.mk to match your local setup (Raven is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install (if
necessary as root):

```
make clean install
```

### Running Raven

Add the following line to your .xinitrc or .xsession to start Raven
using startx:

```
exec raven
```

In order to connect Raven to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec raven

(This will start Raven on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec raven


### Configuration

Configuration is done by creating a custom config.h and (re)compiling
the source code (for now).

-------

#### _See LICENSE file for copyright and license details_
