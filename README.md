"Raven" is a dynamic window manager, forked from my [custom build of Suckless' dwm](https://github.com/I-LeCorbeau/dwm). The end goal is to rewrite it using the xcb library instead of xlib.

```
Important note: this is still in development. If you want to try it, get the raven-base  
release instead of using the git version. While raven-base is currently even with the git  
main branch, this will inevitably change as the xcb rewrite occurs.
```

### Current features (or lack thereof)

  * No default status bar. Not because I don't like dwm's bar (quite the contrary), but because I'm not a fan of having it coded into the window manager.
  * Which means most status bars with the 'override_redirect' option will work. 
  * Tags have basic [ewmh](https://dwm.suckless.org/patches/ewmhtags/) support, so Polybar's xworkspace module works (though no click and scroll, yet).
  * No spawn function, therefore no way to create keybindings in config.h to launch applications. Programs like sxhkd and xbindkeys are more appropriate for that.
  * Which means there's no default keybind to launch a terminal or dmenu.
  * Layouts can be set [pertag](https://dwm.suckless.org/patches/pertag/).
  * Available layouts: tile (default master stack layout), rightmaster, top master/bottom stack, monocle, floating.
  * [Gaps](https://dwm.suckless.org/patches/fullgaps/) are present by default, even in monocle mode.

For usage instructions (keybindings, etc...) start reading the manpage.

### TODO
- Restructure the code to adhere to OpenBSD's KNF [style(9)](https://man.openbsd.org/style)
- XCB rewrite with version 1.0 (underway)

-----------------

Requirements
------------
In order to build Raven you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (raven is installed into
the /usr/local namespace by default).

On OpenBSD: comment (#) FREETYPEINC at line 19, and uncomment the one at line 21 (under # OpenBSD).

Afterwards enter the following command to build and install raven (if
necessary as root):

    make clean install


Running raven
-----------
Add the following line to your .xinitrc to start raven using startx:

    exec raven

In order to connect raven to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec raven

(This will start raven on display :1 of the host foo.bar.)

Configuration
-------------
The configuration of raven is done by creating a custom config.h
and (re)compiling the source code.

-------

#### _See LICENSE file for copyright and license details_
