"Raven" is a dynamic window manager, forked from dwm. This is a work in progress. It works perfectly fine, but it's incomplete. "Raven" might just be a temporary name, I just needed a different name to not mix it up with my custom build of dwm.

The end goal is to rewrite it using the xcb library instead of xlib. Work has already begun on that (because sometimes I get ahead of myself). I have no idea how much of dwm's original code will be left once that is done, since I'm planning on rewriting a lot of functions from scratch, but it will still function like dwm for the most part.

### Current features (or lack thereof)

  * No default status bar. Not because I don't like dwm's bar (quite the contrary), but because I'm not a fan of having it coded into the window manager.
  * Which means most status bar will work (thanks to mihirlad's anybar patch, which was only slightly modified). Tested bars and confirmed to work perfectly: Polybar, Tint2, Lemonbar, Conky.
  * Tags have basic [ewmh](https://dwm.suckless.org/patches/ewmhtags/) features, so Polybar's xworkspace module works (though no click and scroll, yet). Tint2's "desktop name" works as well.
  * No spawn function, therefore no way to create keybindings in config.h to launch applications. Programs like sxhkd and xbindkeys are more appropriate for that.
  * Which means there's no default keybind to launch a terminal or dmenu.
  * [Gaps](https://dwm.suckless.org/patches/fullgaps/) are present by default.
  * Layouts can be set [pertag](https://dwm.suckless.org/patches/pertag/).
  * Available layouts: tile (default master stack layout), right master/left stack, top master/bottom stack, floating, "stackmode" (just monocle mode with gaps, really).

A more appropriate README will be made later. For now, some keybindings not in dwm:

MODKEY is Mod4Mask (aka Super/Windows Key)

MODKEY + Shift + j/k: [Rotatestack](https://dwm.suckless.org/patches/rotatestack/)
MODKEY + r: swap master/stack (right master/left stack)
MODKEY + b: master top/stack bottom
MODKEY + s: stackmode
MODKEY + f: toggle floating
MODKEY + minus/plus: decrease/increase gap size
MODKEY + Shift + minus: toggle gaps on/off

-----------------

Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (raven is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec raven

In order to connect raven to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec raven

(This will start dwm on display :1 of the host foo.bar.)

Configuration
-------------
The configuration of raven is done by creating a custom config.h
and (re)compiling the source code.

-------

#### _See LICENSE file for copyright and license details_
