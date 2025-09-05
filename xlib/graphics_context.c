#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdio.h>

#define XK_MISCELLANY
#include <X11/keysym.h>

/* 
 * More about graphics contexts visit man page -> XCreateGC
 *
 * EXPLANATION OF XGCValues attributes:
 * - function: is the bitwise operation used when a source graphics object
 *     wants to melt with the current drawable. Interpreting the destination 
 *     as our drawable and the source as the graphics object wanting to melt.
 * - plane_mask: what bit planes of a color is the function applied over.
 * - __param__
 *
 *
 * NOTE:
 * XConfigureWindow generates a ConfigureNotify event, if you receive
 * ConfigureNotify events from your OS, better stop the infinite loop when
 * possible.
 */

static Display *disp;
static int screen_num;
static int default_depth;
static Window wroot; //NOTE: a window is a drawable
static XPoint triangle[3];

static XSetWindowAttributes attr = {
  .bit_gravity = CenterGravity,
  .backing_store = NotUseful,
  .save_under = False,
  .override_redirect = False,
  .event_mask = KeyPressMask | StructureNotifyMask
};

static XGCValues gcval = {
  .function = GXcopy,
  .plane_mask = AllPlanes,
  .line_width = 0,
  .line_style = LineSolid,
  .cap_style = CapButt,
  .join_style = JoinMiter,
  .fill_style = FillSolid,
  .fill_rule = EvenOddRule
};

static XWindowChanges wch;


int main()
{
  disp = XOpenDisplay(NULL);
  screen_num = DefaultScreen(disp);
  default_depth = DefaultDepth(disp, screen_num);
  wroot = DefaultRootWindow(disp);

  attr.background_pixel = BlackPixel(disp, screen_num);
  attr.border_pixel = WhitePixel(disp, screen_num);

  wch.width = 800;
  wch.height = 600;
  Window w = XCreateWindow(disp, wroot, 0, 0, 800, 600, 3, 
      default_depth, InputOutput, CopyFromParent,
      CWBitGravity | CWBackingStore | CWSaveUnder | CWEventMask | 
      CWOverrideRedirect, &attr);

  gcval.foreground = WhitePixel(disp, screen_num);
  gcval.background = BlackPixel(disp, screen_num);
  GC gc = XCreateGC(disp, w,
      GCForeground | GCBackground | GCCapStyle | GCJoinStyle,
      &gcval);

  XSetGraphicsExposures(disp, gc, True);
  XMapWindow(disp, w);
  XEvent ev;
  while(1)
  {
    XNextEvent(disp, &ev);
    XClearWindow(disp, w);
    switch(ev.type)
    {
      case ConfigureNotify: // Because my tiling wm changes it
        wch.x = ev.xconfigure.x;
        wch.y = ev.xconfigure.y;
        wch.width = ev.xconfigure.width;
        wch.height = ev.xconfigure.height;
        XConfigureWindow(disp, w, CWX | CWY | CWHeight | CWWidth, &wch);
        //TODO: XConfigureWindow generates a ConfigureNotify loop
        break;
      case KeyPress:
        KeySym ks = XLookupKeysym(&ev.xkey, 0);
        if(ks == XK_Escape) {
          XFreeGC(disp, gc);
          XDestroyWindow(disp, w);
          XCloseDisplay(disp);
          return 0;
        }
    }
    triangle[0].x = wch.width / 2;
    triangle[0].y = (wch.height / 2) - (wch.height / 4);
    triangle[1].x = (wch.width / 2) - (wch.width / 4);
    triangle[1].y = (wch.height / 2) + (wch.height / 4);
    triangle[2].x = (wch.width / 2) + (wch.width / 4);
    triangle[2].y = (wch.height / 2) + (wch.height / 4);
    XFillPolygon(disp, w, gc, triangle, 3, Convex, CoordModeOrigin);
    XFlush(disp);
  }
}
