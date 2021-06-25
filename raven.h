#ifndef RAVEN_H
#define RAVEN_H

#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif /* XINERAMA */
#include <X11/Xft/Xft.h>

/* macros */
#define BUTTONMASK              (ButtonPressMask|ButtonReleaseMask)
#define CLEANMASK(mask)         (mask & ~(numlockmask|LockMask) & (ShiftMask|ControlMask|Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask))
#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))
#define INTERSECT(x,y,w,h,m)    (MAX(0, MIN((x)+(w),(m)->mx+(m)->mw) - MAX((x),(m)->mx)) \
                               * MAX(0, MIN((y)+(h),(m)->my+(m)->mh) - MAX((y),(m)->my)))
#define ISVISIBLE(C)            ((C->tags & C->mon->tagset[C->mon->seltags]))
#define LENGTH(X)               (sizeof X / sizeof X[0])
#define MOUSEMASK               (BUTTONMASK|PointerMotionMask)
#define WIDTH(X)                ((X)->w + 2 * (X)->bw)
#define HEIGHT(X)               ((X)->h + 2 * (X)->bw)
#define TAGMASK                 ((1 << LENGTH(tags)) - 1)
#define TAGSLENGTH              (LENGTH(tags))

/* enums */
enum { CurNormal, CurResize, CurMove, CurLast };				/* cursor */
enum { SchemeNorm, SchemeSel };							/* color schemes */
enum { ColFg, ColBg, ColBorder };						/* Clr scheme index */
enum { NetSupported, NetWMName, NetWMState, NetWMCheck,
       NetWMFullscreen, NetActiveWindow, NetWMWindowType,
       NetWMWindowTypeDialog, NetClientList, NetDesktopNames, 
       NetDesktopViewport, NetNumberOfDesktops, NetCurrentDesktop, NetLast };	/* EWMH atoms */
enum { WMProtocols, WMDelete, WMState, WMTakeFocus, WMLast };			/* default atoms */
enum { ClkClientWin, ClkRootWin };						/* clicks */

typedef union {
	int		 i;
	unsigned int	 ui;
	float		 f;
	const void 	*v;
} Arg;

struct Button {
	unsigned int	 click;
	unsigned int	 mask;
	unsigned int	 button;
	void		 (*func)(const Arg *arg);
	const		 Arg arg;
};

struct Client {
	char		 name[256];
	float		 mina, maxa;
	int		 x, y, w, h;
	int		 oldx, oldy, oldw, oldh;
	int		 basew, baseh, incw, inch, maxw, maxh, minw, minh;
	int		 bw, oldbw;
	unsigned int	 tags;
	int		 isfixed, isfloating, isurgent, neverfocus, oldstate, isfullscreen;
	struct Client	*next;
	struct Client	*snext;
	struct Monitor	*mon;
	Window		 win;
};

typedef struct {
	Cursor cursor;
} Cur;

typedef struct Fnt {
	Display		*dpy;
	unsigned int	 h;
	XftFont		*xfont;
	FcPattern	*pattern;
	struct Fnt	*next;
} Fnt;

typedef XftColor Clr;

typedef struct {
	unsigned int w, h;
	Display *dpy;
	int screen;
	Window root;
	Drawable drawable;
	GC gc;
	Clr *scheme;
	Fnt *fonts;
} Drw;

struct Key {
	unsigned int	 mod;
	KeySym		 keysym;
	void		 (*func)(const Arg *);
	const		 Arg arg;
};

struct Layout {
	const char	*symbol;
	void		(*arrange)(struct Monitor *);
};

typedef struct Pertag Pertag;
struct Monitor {
	char			 ltsymbol[16];
	float			 mfact;
	int			 nmaster;
	int			 num;
	int			 by, bh;           /* bar geometry */
	int			 mx, my, mw, mh;   /* screen size */
	int			 wx, wy, ww, wh;   /* window area  */
	int			 gappx;            /* gap size */
	unsigned int		 seltags;
	unsigned int		 sellt;
	unsigned int		 tagset[2];
	int			 showbar;
	int			 topbar;
	struct Client		*clients;
	struct Client		*sel;
	struct Client		*stack;
	struct Monitor		*next;
	Window			 barwin;
	const struct Layout	*lt[2];
	struct Pertag		*pertag;
};

struct Rule {
	const char	*class;
	const char	*instance;
	const char	*title;
	unsigned int	 tags;
	int		 isfloating;
	int		 monitor;
};

/* variables */
extern const char	 broken[];
extern int		 screen;
extern int		 sw, sh;
extern int		 bh;
extern int		 (*xerrorxlib)(Display *, XErrorEvent *);
extern unsigned int	 numlockmask;
extern void		 (*handler[LASTEvent]) (XEvent *);
extern Atom		 wmatom[WMLast], netatom[NetLast];
extern int		 running;
extern Cur		*cursor[CurLast];
extern Clr		**scheme;
extern Display		*dpy;
extern Drw		*drw;
extern struct Monitor	*mons, *selmon;
extern Window		 root, wmcheckwin;

/* function declarations */
void		 applyrules(struct Client *c);
int		 applysizehints(struct Client *c, int *, int *, int *, int *, int);
void		 arrange(struct Monitor *m);
void		 arrangemon(struct Monitor *m);
void		 attach(struct Client *c);
void		 attachstack(struct Client *c);
void		 buttonpress(XEvent *e);
void		 checkotherwm(void);
void		 cleanup(void);
void		 cleanupmon(struct Monitor *mon);
void		 clientmessage(XEvent *e);
void		 configure(struct Client *c);
void		 configurenotify(XEvent *e);
void		 configurerequest(XEvent *e);
struct Monitor	*createmon(void);
void		 destroynotify(XEvent *e);
void		 detach(struct Client *c);
void		 detachstack(struct Client *c);
struct Monitor	*dirtomon(int dir);
Drw *drw_create(Display *dpy, int screen, Window win, unsigned int w, unsigned int h);
void drw_resize(Drw *drw, unsigned int w, unsigned int h);
void drw_free(Drw *drw);
void drw_clr_create(Drw *drw, Clr *dest, const char *clrname);
Clr *drw_scm_create(Drw *drw, const char *clrnames[], size_t clrcount);
Cur *drw_cur_create(Drw *drw, int shape);
void drw_cur_free(Drw *drw, Cur *cursor);
void drw_setscheme(Drw *drw, Clr *scm);
void drw_rect(Drw *drw, int x, int y, unsigned int w, unsigned int h, int filled, int invert);
void drw_map(Drw *drw, Window win, int x, int y, unsigned int w, unsigned int h);
void		 enqueue(struct Client *c);
void		 enqueuestack(struct Client *c);
void		 enternotify(XEvent *e);
void		 focus(struct Client *c);
void		 focusin(XEvent *e);
void		 focusmon(const Arg *arg);
void		 focusstack(const Arg *arg);
int		 getrootptr(int *x, int *y);
long		 getstate(Window w);
int		 gettextprop(Window w, Atom atom, char *text, unsigned int size);
void		 grabbuttons(struct Client *c, int focused);
void		 grabkeys(void);
void		 incnmaster(const Arg *arg);
void		 keypress(XEvent *e);
void		 killclient(const Arg *arg);
void		 manage(Window w, XWindowAttributes *wa);
void		 mappingnotify(XEvent *e);
void		 maprequest(XEvent *e);
void		 motionnotify(XEvent *e);
void		 movemouse(const Arg *arg);
struct Client	*nexttiled(struct Client *c);
void		pop(struct Client *);
void		propertynotify(XEvent *e);
void		quit(const Arg *arg);
struct Monitor	*recttomon(int x, int y, int w, int h);
void		 resize(struct Client *c, int x, int y, int w, int h, int interact);
void		 resizeclient(struct Client *c, int x, int y, int w, int h);
void		 resizemouse(const Arg *arg);
void		 restack(struct Monitor *m);
void		 rotatestack(const Arg *arg);
void		 run(void);
void		 scan(void);
int		 sendevent(struct Client *c, Atom proto);
void		 sendmon(struct Client *c, struct Monitor *m);
void		 setclientstate(struct Client *c, long state);
void		 setcurrenttag(void);
void		 setfocus(struct Client *c);
void		 setfullscreen(struct Client *c, int fullscreen);
void		 setgaps(const Arg *arg);
void		 setlayout(const Arg *arg);
void		 setmfact(const Arg *arg);
void		 setnumtags(void);
void		 settagnames(void);
void		 setup(void);
void		 seturgent(struct Client *c, int urg);
void		 setviewport(void);
void		 showhide(struct Client *c);
void		 sigchld(int unused);
void		 tag(const Arg *arg);
void		 tagmon(const Arg *arg);
void		 togglebar(const Arg *arg);
void		 togglefloating(const Arg *arg);
void		 toggletag(const Arg *arg);
void		 toggleview(const Arg *arg);
void		 unfocus(struct Client *c, int setfocus);
void		 unmanage(struct Client *c, int destroyed);
void		 unmapnotify(XEvent *e);
void		 updatebarpos(struct Monitor *m);
void		 updateclientlist(void);
void		 updatecurrenttag(void);
int		 updategeom(void);
void		 updatenumlockmask(void);
void		 updatesizehints(struct Client *c);
void		 updatetitle(struct Client *c);
void		 updatewindowtype(struct Client *c);
void		 updatewmhints(struct Client *c);
void		 view(const Arg *arg);
struct Client	*wintoclient(Window w);
struct Monitor	*wintomon(Window w);
int		 xerror(Display *dpy, XErrorEvent *ee);
int		 xerrordummy(Display *dpy, XErrorEvent *ee);
int		 xerrorstart(Display *dpy, XErrorEvent *ee);
void		 zoom(const Arg *arg);
void		 die(const char *fmt, ...);
void		*xcalloc(size_t, size_t);

#endif
