#include <X11/Xlib.h>
#include <X11/Xatom.h>

/* 
 * More about graphics contexts visit man page -> XCreateGC
 *
 * EXPLANATION OF XGCValues attributes:
 * - function: is the bitwise operation used when a source graphics object
 *     wants to melt with the current drawable. Interpreting the destination 
 *     as our drawable and the source as the graphics object wanting to melt.
 * - plane_mask: what bit planes of a color is the function applied over.
 * - __param__
 */

static Display *disp;
static int screen_num;
static int default_depth;
static Window wroot; //NOTE: a window is a drawable

static XSetWindowAttributes attr = {
  .bit_gravity = CenterGravity,
  .backing_store = NotUseful,
  .save_under = False,
  .override_redirect = False,
  .event_mask = KeyPressMask | KeyReleaseMask | ExposureMask
};


int main()
{
  disp = XOpenDisplay(NULL);
  screen_number = DefaultScreen(disp);
  default_depth = DefaultDepth(disp, screen_number);
  wroot = DefaultRootWindow(disp);

  attr.background_pixel = BlackPixel(disp, screen_number);
  attr.border_pixel = WhitePixel(disp, screen_number);

  Window w = XCreateWindow(disp, wroot, 0, 0, 800, 600, 3, 
      default_depth, InputOutput, CopyFromParent,
      CWBitGravity | CWBackingStore | CWSaveUnder | CWEventMask,
      &attr);

  Pixmap pmap = XCreatePixmap(disp, w, 100, 100, (unsigned int)default_depth);

  XGCValues gcval = {
    .function = GXcopy,
    .plane_mask = AllPlanes,
    .foreground = WhitePixel(disp, screen_num),
    .background = Blackpixel(disp, screen_num),
    .line_width = 0,
    .line_style = LineSolid,
    .cap_style = CapButt,
    .join_style = JoinMiter,
    .fill_style = FillSolid,
    .fill_rule = EvenOddRule
      //TODO: continue here
  };
  GC gc = XCreateGC(disp, w, 
      GCPlaneMask | GCForeground | GCBackground | GCCapStyle | GCJoinStyle, 
      &gcval);

  XSetGraphicsExposures(dips, gc, False);

  // A lot of functions that probably will use later but not now, later...

  //TODO: drawing something and putting a loop

  XFreeGC(disp, gc);
  XFreePixmap(pmap);
  XDestroyWindow(disp, w);
  XCLoseDisplay(disp);
  return 0;
}
