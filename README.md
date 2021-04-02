"Raven" is a dynamic window manager, forked from dwm. This is a work in progress. It works perfectly fine, but it's incomplete. "Raven" might just be a temporary name, I just needed a different name to not mix it up with my custom build of dwm.

The end goal is to rewrite it using the xcb library instead of xlib. Work has already begun on that (because sometimes I get ahead of myself). I have no idea how much of dwm's original code will be left once that is done, since I'm planning on rewriting a lot of functions from scratch, but it will still function like dwm for the most part.

### Current features (or lack thereof)

  * No default status bar. Not because I don't like dwm's bar (quite the contrary), but because I'm not a fan of having it coded into the window manager.
  * Which means most status bar with the 'override_redirect' option will work. 
  * Tags have basic [ewmh](https://dwm.suckless.org/patches/ewmhtags/) features, so Polybar's xworkspace module works (though no click and scroll, yet).
  * No spawn function, therefore no way to create keybindings in config.h to launch applications. Programs like sxhkd and xbindkeys are more appropriate for that.
  * Which means there's no default keybind to launch a terminal or dmenu.
  * [Gaps](https://dwm.suckless.org/patches/fullgaps/) are present by default.
  * Layouts can be set [pertag](https://dwm.suckless.org/patches/pertag/).
  * Available layouts: tile (default master stack layout), right master/left stack, top master/bottom stack, floating, "stackmode" (just monocle mode with gaps, really).

Bug: the only bug that I'm aware of is very specific and relates to Polybar. If for some reason Polybar is relaunched from a terminal, sometimes the ewmh module will crash, with the only message being: disabling module "ewmh" (reason: XCB_WINDOW(3)). Pretty sure I know the underlying cause, but this issue is so small that I'll probably wait for the xcb rewrite to fix it. In the meantime, simply closing the terminal, reopening it and relaunching Polybar will fix the problem. No need to log out of X and log back in.

For usage instructions (keybindings, etc...) start reading the manpage.

-----------------

Requirements
------------
In order to build Raven you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (raven is installed into
the /usr/local namespace by default).

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
